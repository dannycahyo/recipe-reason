type recipeType = {
  _id: string,
  title: string,
  category: string,
  image: string,
  ingredients: string,
  instruction: string,
};

type editModeState =
  | Show
  | Edit;

[@react.component]
let make =
    (
      ~recipe: recipeType,
      ~onDeleteRecipe: string => unit,
      ~onEditRecipe:
         (
           ~recipeId: string,
           ~title: string,
           ~category: string,
           ~imageUrl: string,
           ~ingredients: string,
           ~instruction: string
         ) =>
         unit,
    ) => {
  let (editModeState, setEditModeState) = React.useState(() => Show);

  let (recipeTitleValue, setRecipeTitleValue) = React.useState(() => "");
  let (recipeCategoryValue, setRecipeCategoryValue) =
    React.useState(() => "");
  let (recipeImageValue, setRecipeImageValue) = React.useState(() => "");
  let (recipeIngredientsValue, setRecipeIngredientsValue) =
    React.useState(() => "");
  let (recipeInstructionValue, setRecipeInstructionValue) =
    React.useState(() => "");
  ();

  <div
    className="bg-white shadow overflow-hidden sm:rounded-lg" key={recipe._id}>
    <div className="px-4 py-5 sm:px-6">
      <h3 className="text-lg leading-6 font-medium text-gray-900">
        "Recipe Details"->React.string
      </h3>
      <p className=" max-w-2xl text-sm text-gray-500">
        "Information Details About The Recipe"->React.string
      </p>
    </div>
    {switch (editModeState) {
     | Show =>
       <>
         <div className="border-t border-gray-200">
           <dl>
             <div className="bg-gray-50 px-4 py-5">
               <img src={recipe.image} alt={recipe.title} />
             </div>
             <div
               className="bg-gray-50 px-4 py-5 sm:grid sm:grid-cols-3 sm:gap-4 sm:px-6">
               <dt className="text-sm font-medium text-gray-500">
                 "Recipe Name"->React.string
               </dt>
               <dd className=" text-sm text-gray-900 sm:mt-0 sm:col-span-2">
                 recipe.title->React.string
               </dd>
             </div>
             <div
               className="bg-white px-4 py-5 sm:grid sm:grid-cols-3 sm:gap-4 sm:px-6">
               <dt className="text-sm font-medium text-gray-500">
                 "Category"->React.string
               </dt>
               <dd className=" text-sm text-gray-900 sm:mt-0 sm:col-span-2">
                 recipe.category->React.string
               </dd>
             </div>
             <div className="bg-gray-50 px-4 py-5">
               <dt className="text-sm font-medium text-gray-500">
                 "Ingredients"->React.string
               </dt>
               <dd className=" text-sm text-gray-900 sm:mt-0 sm:col-span-2">
                 recipe.ingredients->React.string
               </dd>
             </div>
             <div className="bg-white px-4 py-5">
               <dt className="text-sm font-medium text-gray-500">
                 "Instruction"->React.string
               </dt>
               <dd className=" text-sm text-gray-900 sm:mt-0 sm:col-span-2">
                 recipe.instruction->React.string
               </dd>
             </div>
           </dl>
         </div>
         <div className="flex justify-center items-center pb-6">
           <button
             onClick={_ => {
               setRecipeTitleValue(_ => recipe.title);
               setRecipeCategoryValue(_ => recipe.category);
               setRecipeImageValue(_ => recipe.image);
               setRecipeIngredientsValue(_ => recipe.ingredients);
               setRecipeInstructionValue(_ => recipe.instruction);

               setEditModeState(_ => Edit);
             }}
             className="w-full rounded-md border border-transparent shadow-sm px-4 py-2 bg-blue-600 text-base font-medium text-white hover:bg-blue-500 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-red-500 sm:ml-3 sm:w-auto sm:text-sm">
             "Edit"->React.string
           </button>
           <button
             onClick={_ => onDeleteRecipe(recipe._id)}
             className="w-full rounded-md border border-transparent shadow-sm px-4 py-2 bg-red-600 text-base font-medium text-white hover:bg-red-500 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-red-500 sm:ml-3 sm:w-auto sm:text-sm">
             "Delete"->React.string
           </button>
         </div>
       </>
     | Edit =>
       <>
         <div className="border-t border-gray-200">
           <dl>
             <div
               className="bg-gray-50 px-2 py-5 sm:grid sm:grid-cols-3 sm:gap-4 sm:px-6">
               <dt className="text-sm font-medium text-gray-500">
                 "Recipe Name"->React.string
               </dt>
               <input
                 type_="text"
                 name="recipe"
                 id="recipe"
                 className=" focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                 value=recipeTitleValue
                 onChange={event => {
                   let value = event->ReactEvent.Form.target##value;
                   setRecipeTitleValue(_ => value);
                 }}
               />
             </div>
             <div
               className="bg-white px-2 py-5 sm:grid sm:grid-cols-3 sm:gap-4 sm:px-6">
               <dt className="text-sm font-medium text-gray-500">
                 "Category"->React.string
               </dt>
               <input
                 type_="text"
                 name="category"
                 id="category"
                 className=" focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                 value=recipeCategoryValue
                 onChange={event => {
                   let value = event->ReactEvent.Form.target##value;
                   setRecipeCategoryValue(_ => value);
                 }}
               />
             </div>
             <div
               className="bg-white px-2 py-5 sm:grid sm:grid-cols-3 sm:gap-4 sm:px-6">
               <dt className="text-sm font-medium text-gray-500">
                 "Image"->React.string
               </dt>
               <input
                 type_="text"
                 name="image"
                 id="image"
                 className=" focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                 value=recipeImageValue
                 onChange={event => {
                   let value = event->ReactEvent.Form.target##value;
                   setRecipeImageValue(_ => value);
                 }}
               />
             </div>
             <div className="bg-gray-50 px-2 py-5">
               <dt className="text-sm font-medium text-gray-500">
                 "Ingredients"->React.string
               </dt>
               <textarea
                 type_="text"
                 name="ingredients"
                 id="ingredients"
                 className=" focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                 value=recipeIngredientsValue
                 onChange={event => {
                   let value = event->ReactEvent.Form.target##value;
                   setRecipeIngredientsValue(_ => value);
                 }}
               />
             </div>
             <div className="bg-white px-2 py-5">
               <dt className="text-sm font-medium text-gray-500">
                 "Instruction"->React.string
               </dt>
               <textarea
                 type_="text"
                 name="instruction"
                 id="instruction"
                 className=" focus:ring-indigo-500 focus:border-indigo-500 block w-full shadow-sm sm:text-sm border-4 border-blue-200 rounded-md"
                 value=recipeInstructionValue
                 onChange={event => {
                   let value = event->ReactEvent.Form.target##value;
                   setRecipeInstructionValue(_ => value);
                 }}
               />
             </div>
           </dl>
         </div>
         <div className="flex justify-center items-center pb-6">
           <button
             onClick={_ => {
               onEditRecipe(
                 ~recipeId=recipe._id,
                 ~title=recipeTitleValue,
                 ~category=recipeCategoryValue,
                 ~imageUrl=recipeImageValue,
                 ~ingredients=recipeIngredientsValue,
                 ~instruction=recipeInstructionValue,
               );
               setEditModeState(_ => Show);
             }}
             className="w-full rounded-md border border-transparent shadow-sm px-4 py-2 bg-blue-600 text-base font-medium text-white hover:bg-blue-500 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-red-500 sm:ml-3 sm:w-auto sm:text-sm">
             "Submit"->React.string
           </button>
         </div>
       </>
     }}
  </div>;
};
