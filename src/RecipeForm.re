type postRecipeState =
  | IdlePost
  | LoadingPost
  | SuccesPost
  | FailurePost;

[@react.component]
let make = () => {
  let (postRecipeState, setPostRecipeState) = React.useState(() => IdlePost);

  let (recipeTitleValue, setRecipeTitleValue) = React.useState(() => "");
  let (recipeCategoryValue, setRecipeCategoryValue) =
    React.useState(() => "");
  let (recipeImageValue, setRecipeImageValue) = React.useState(() => "");
  let (recipeIngredientsValue, setRecipeIngredientsValue) =
    React.useState(() => "");
  let (recipeInstructionValue, setRecipeInstructionValue) =
    React.useState(() => "");

  let handleAddRecipe = () => {
    let newRecipe = Js.Dict.empty();

    Js.Dict.set(newRecipe, "title", Js.Json.string(recipeTitleValue));
    Js.Dict.set(newRecipe, "category", Js.Json.string(recipeCategoryValue));
    Js.Dict.set(newRecipe, "image", Js.Json.string(recipeImageValue));
    Js.Dict.set(
      newRecipe,
      "ingredients",
      Js.Json.string(recipeIngredientsValue),
    );
    Js.Dict.set(
      newRecipe,
      "instruction",
      Js.Json.string(recipeInstructionValue),
    );
    setPostRecipeState(_ => IdlePost);

    setPostRecipeState(_ => LoadingPost);
    Js.Promise.(
      Fetch.fetchWithInit(
        "https://recipesappapi.herokuapp.com/recipe",
        Fetch.RequestInit.make(
          ~method_=Post,
          ~headers=
            Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          ~body=
            Fetch.BodyInit.make(
              Js.Json.stringify(Js.Json.object_(newRecipe)),
            ),
          (),
        ),
      )
      |> then_(Fetch.Response.json)
      |> then_(_ => {
           setPostRecipeState(_ => SuccesPost);
           Js.Promise.resolve();
         })
      |> catch(_ => {
           setPostRecipeState(_ => FailurePost);
           Js.Promise.resolve();
         })
      |> ignore
    );

    setRecipeTitleValue(_ => "");
    setRecipeCategoryValue(_ => "");
    setRecipeIngredientsValue(_ => "");
    setRecipeInstructionValue(_ => "");
    setRecipeImageValue(_ => "");
  };

  <div className="mt-10 sm:mt-0">
    <div className="md:grid md:grid-cols-3 md:gap-6">
      <div className="md:col-span-1">
        <div className="px-4 sm:px-0">
          <h3 className="text-lg font-medium leading-6 text-gray-900">
            "Recipe Dashboard"->React.string
          </h3>
          <p className="mt-1 text-sm text-gray-600">
            "Please kindly add the new recipe!"->React.string
          </p>
        </div>
      </div>
      <div className="mt-5 md:mt-0 md:col-span-2">
        <div className="shadow overflow-hidden sm:rounded-md">
          <div className="px-4 py-5 bg-white sm:p-6">
            <div className="grid grid-cols-6 gap-6">
              <div className="col-span-6 sm:col-span-3">
                <label className="block text-sm font-medium text-gray-700">
                  "Recipe Name"->React.string
                </label>
                <input
                  type_="text"
                  name="recipe"
                  id="recipe"
                  className="mt-1 focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                  value=recipeTitleValue
                  onChange={event => {
                    let value = event->ReactEvent.Form.target##value;
                    setRecipeTitleValue(_ => value);
                  }}
                />
              </div>
              <div className="col-span-6 sm:col-span-3">
                <label className="block text-sm font-medium text-gray-700">
                  "Category"->React.string
                </label>
                <input
                  type_="text"
                  name="category"
                  id="category"
                  className="mt-1 focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                  value=recipeCategoryValue
                  onChange={event => {
                    let value = event->ReactEvent.Form.target##value;
                    setRecipeCategoryValue(_ => value);
                  }}
                />
              </div>
              <div className="col-span-6 sm:col-span-4">
                <label className="block text-sm font-medium text-gray-700">
                  "Image URL"->React.string
                </label>
                <input
                  type_="text"
                  name="imageurl"
                  id="imageurl"
                  className="mt-1 focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                  value=recipeImageValue
                  onChange={event => {
                    let value = event->ReactEvent.Form.target##value;
                    setRecipeImageValue(_ => value);
                  }}
                />
              </div>
              <div className="col-span-6">
                <label className="block text-sm font-medium text-gray-700">
                  "Ingredients"->React.string
                </label>
                <textarea
                  type_="text"
                  name="ingredients"
                  id="ingredients"
                  className="mt-1 focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                  value=recipeIngredientsValue
                  onChange={event => {
                    let value = event->ReactEvent.Form.target##value;
                    setRecipeIngredientsValue(_ => value);
                  }}
                />
              </div>
              <div className="col-span-6">
                <label className="block text-sm font-medium text-gray-700">
                  "Instruction"->React.string
                </label>
                <textarea
                  type_="text"
                  name="instruction"
                  id="instruction"
                  className="mt-1 focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                  value=recipeInstructionValue
                  onChange={event => {
                    let value = event->ReactEvent.Form.target##value;
                    setRecipeInstructionValue(_ => value);
                  }}
                />
              </div>
            </div>
          </div>
          <div className="px-4 py-3 bg-gray-50 text-right sm:px-6">
            <button
              onClick={_ => {handleAddRecipe()}}
              className="inline-flex justify-center py-2 px-4 border border-transparent shadow-sm text-sm font-medium rounded-md text-white bg-indigo-600 hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-indigo-500">
              "Submit"->React.string
            </button>
          </div>
        </div>
      </div>
    </div>
    <div>
      {switch (postRecipeState) {
       | IdlePost => React.null
       | LoadingPost =>
         <RecipeModal
           notes="Loading...."
           description="Please wait for a while"
           buttonTitle=""
           onClose={_ => ()}
         />
       | FailurePost =>
         <RecipeModal
           notes="Failure!"
           description="Something unexpected happened, please try again"
           buttonTitle="Retry"
           onClose={_ => setPostRecipeState(_ => IdlePost)}
         />
       | SuccesPost =>
         <RecipeModal
           notes="Success"
           description="You've already added new recipe! You can check it out on my recipe page"
           buttonTitle="OK"
           onClose={_ => setPostRecipeState(_ => IdlePost)}
         />
       }}
    </div>
  </div>;
};
