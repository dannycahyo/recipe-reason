[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

type getRecipeState =
  | IdleGet
  | LoadingGetStatus
  | Succes(array(RecipeDetail.recipeType))
  | FailureGetStatus
  | EmptyRecipe;

type editRecipeState =
  | IdleEdit
  | LoadingEditStatus
  | SuccesEditStatus
  | FailureEditStatus;

type deleteRecipeState =
  | IdleDelete
  | LoadingDeleteStatus
  | SuccesDeleteStatus
  | FailureDeleteStatus;

type editModeState =
  | Show
  | Edit;

[@react.component]
let make = () => {
  let (getRecipeState, setGetRecipeState) = React.useState(() => IdleGet);
  let (deleteRecipeState, setDeleteRecipeState) =
    React.useState(() => IdleDelete);
  let (editRecipeState, setEditRecipeState) = React.useState(() => IdleEdit);

  React.useEffect0(() => {
    setGetRecipeState(_prevState => LoadingGetStatus);
    Js.Promise.(
      fetch("https://recipesappapi.herokuapp.com/recipe")
      |> then_(response => response##json())
      |> then_(jsonResponse => {
           setGetRecipeState(_prevTodos =>
             jsonResponse->Js.Array2.length > 0
               ? Succes(jsonResponse) : EmptyRecipe
           );
           Js.Promise.resolve();
         })
      |> catch(_ => {
           setGetRecipeState(_prevState => FailureGetStatus);
           Js.Promise.resolve();
         })
      |> ignore
    );
    None;
  });

  let handleDeleteRecipe = (recipes, recipeId: string) => {
    setDeleteRecipeState(_ => LoadingDeleteStatus);
    Js.Promise.(
      Fetch.fetchWithInit(
        "https://recipesappapi.herokuapp.com/recipe/" ++ recipeId,
        Fetch.RequestInit.make(~method_=Delete, ()),
      )
      |> then_(Fetch.Response.json)
      |> then_(_ => {
           setDeleteRecipeState(_ => SuccesDeleteStatus);
           Js.Promise.resolve();
         })
      |> catch(_ => {
           setDeleteRecipeState(_ => FailureDeleteStatus);
           Js.Promise.resolve();
         })
      |> ignore
    );

    // Trigger re-render with updated data
    let updatedRecipe: array(RecipeDetail.recipeType) =
      recipes->Js.Array2.filter((recipe: RecipeDetail.recipeType) =>
        recipe._id !== recipeId
      );

    setGetRecipeState(_ => Succes(updatedRecipe));
  };

  let handleEditRecipe =
      (
        ~recipeId,
        ~recipes,
        ~title,
        ~category,
        ~imageUrl,
        ~ingredients,
        ~instruction,
      ) => {
    let updatedRecipeJson = Js.Dict.empty();
    Js.Dict.set(updatedRecipeJson, "id", Js.Json.string(recipeId));
    Js.Dict.set(updatedRecipeJson, "title", Js.Json.string(title));
    Js.Dict.set(updatedRecipeJson, "category", Js.Json.string(category));
    Js.Dict.set(updatedRecipeJson, "imageUrl", Js.Json.string(imageUrl));
    Js.Dict.set(
      updatedRecipeJson,
      "ingredients",
      Js.Json.string(ingredients),
    );
    Js.Dict.set(
      updatedRecipeJson,
      "instruction",
      Js.Json.string(instruction),
    );

    setEditRecipeState(_ => LoadingEditStatus);
    Js.Promise.(
      Fetch.fetchWithInit(
        "https://recipesappapi.herokuapp.com/recipe/" ++ recipeId,
        Fetch.RequestInit.make(
          ~method_=Put,
          ~headers=
            Fetch.HeadersInit.make({"Content-Type": "application/json"}),
          ~body=
            Fetch.BodyInit.make(
              Js.Json.stringify(Js.Json.object_(updatedRecipeJson)),
            ),
          (),
        ),
      )
      |> then_(Fetch.Response.json)
      |> then_(_ => {
           setEditRecipeState(_ => SuccesEditStatus);
           Js.Promise.resolve();
         })
      |> catch(_ => {
           setEditRecipeState(_ => FailureEditStatus);
           Js.Promise.resolve();
         })
      |> ignore
    );

    let editedRecipeIndex =
      recipes->Js.Array2.findIndex((recipe: RecipeDetail.recipeType) =>
        recipe._id === recipeId
      );

    let updatedRecipe: RecipeDetail.recipeType = {
      _id: recipeId,
      title,
      category,
      image: imageUrl,
      ingredients,
      instruction,
    };

    let updatedRecipes: array(RecipeDetail.recipeType) =
      Array.append([||], recipes);
    updatedRecipes[editedRecipeIndex] = updatedRecipe;

    setGetRecipeState(_ => Succes(updatedRecipes));
  };

  <div className="grid gap-4 grid-cols-3 grid-rows-3">
    {switch (getRecipeState) {
     | IdleGet
     | LoadingGetStatus =>
       <RecipeModal
         notes="Loading"
         description="Please wait for a while"
         buttonTitle=""
         onClose={_ => ()}
       />
     | FailureGetStatus =>
       <RecipeModal
         notes="Failure!"
         description="Something unexpected happened, please try again"
         buttonTitle="Retry"
         onClose={_ => setGetRecipeState(_ => IdleGet)}
       />
     | EmptyRecipe => "There is no recipe yet"->React.string
     | Succes(recipeData) =>
       <>
         {{
            recipeData->Belt.Array.map(recipe => {
              <RecipeDetail
                key={recipe._id}
                recipe
                onDeleteRecipe={id => handleDeleteRecipe(recipeData, id)}
                onEditRecipe={(
                  ~recipeId: string,
                  ~title: string,
                  ~category: string,
                  ~imageUrl: string,
                  ~ingredients: string,
                  ~instruction: string,
                ) =>
                  handleEditRecipe(
                    ~recipeId,
                    ~title,
                    ~category,
                    ~imageUrl,
                    ~ingredients,
                    ~instruction,
                    ~recipes=recipeData,
                  )
                }
              />
            });
          }
          ->React.array}
       </>
     }}
    <div>
      {switch (deleteRecipeState) {
       | IdleDelete => React.null
       | LoadingDeleteStatus =>
         <RecipeModal
           notes="Loading"
           description="Please wait for a while"
           buttonTitle=""
           onClose={_ => ()}
         />
       | FailureDeleteStatus =>
         <RecipeModal
           notes="Failure!"
           description="Something unexpected happened, please try again"
           buttonTitle="Retry"
           onClose={_ => setDeleteRecipeState(_ => IdleDelete)}
         />
       | SuccesDeleteStatus =>
         <RecipeModal
           notes="Success"
           description="You've already deleted tghe targeted recipe! You can check it out again!"
           buttonTitle="OK"
           onClose={_ => setDeleteRecipeState(_ => IdleDelete)}
         />
       }}
    </div>
    <div>
      {switch (editRecipeState) {
       | IdleEdit => React.null
       | LoadingEditStatus =>
         <RecipeModal
           notes="Loading"
           description="Please wait for a while"
           buttonTitle=""
           onClose={_ => ()}
         />
       | FailureEditStatus =>
         <RecipeModal
           notes="Failure!"
           description="Something unexpected happened, please try again"
           buttonTitle="Retry"
           onClose={_ => setEditRecipeState(_ => IdleEdit)}
         />
       | SuccesEditStatus =>
         <RecipeModal
           notes="Success"
           description="You've already edited the targeted recipe!"
           buttonTitle="OK"
           onClose={_ => setEditRecipeState(_ => IdleEdit)}
         />
       }}
    </div>
  </div>;
};
