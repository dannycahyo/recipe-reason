[@react.component]
let make = (~notes, ~description, ~buttonTitle, ~onClose: unit => unit) => {
  <div
    className="fixed z-10 inset-0 overflow-y-auto"
    ariaLabelledby="modal-title"
    role="dialog">
    <div
      className="flex items-end justify-center min-h-screen pt-4 px-4 pb-20 text-center sm:block sm:p-0">
      <div
        className="fixed inset-0 bg-gray-500 bg-opacity-75 transition-opacity"
        ariaHidden=true
      />
      <div
        className="inline-block align-bottom bg-white rounded-lg text-left overflow-hidden shadow-xl transform transition-all sm:my-8 sm:align-middle sm:max-w-lg sm:w-full">
        <div className="bg-white px-4 pt-5 pb-4 sm:p-6 sm:pb-4">
          <div className="sm:flex sm:items-start">
            <div className="mt-3 text-center sm:mt-0 sm:ml-4 sm:text-left">
              <h3
                className="text-lg leading-6 font-medium text-gray-900"
                id="modal-title">
                notes->React.string
              </h3>
              <div className="mt-2">
                <p className="text-sm text-gray-500">
                  description->React.string
                </p>
              </div>
            </div>
          </div>
        </div>
        <div
          className="bg-gray-50 px-4 py-3 sm:px-6 sm:flex sm:flex-row-reverse">
          <button
            type_="button"
            onClick={_ => onClose()}
            className="w-full inline-flex justify-center rounded-md border border-transparent shadow-sm px-4 py-2 bg-blue-600 text-base font-medium text-white hover:bg-blue-500 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-red-500 sm:ml-3 sm:w-auto sm:text-sm">
            buttonTitle->React.string
          </button>
        </div>
      </div>
    </div>
  </div>;
};
