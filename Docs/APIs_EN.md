## DateTime

Used to get the current DateTime, return YYYY-MM-DD HH:MM:SS

- `DateTime::getCurrentDateTime()`


## Message

Output the error message with Red color

- `Message::error(string message)`

Output the warning message with Yellow color

- `Message::warning(string message)`

Output the sucsess message with Green color

- `Message::success(string message)`

Output the notice message with Blue color

- `Message::notice(string message)`


## Menu

Validate the input option is digit or in the range, return -1 means error

- `Menu::validOption(string input, int maxOption)`


## Form

Valid the input details when registration is match the format(regex) or not, accept quit option when the process

- `string validateInput(string prompt, string hint,string regexStr) `

Asked for the option which need to proceed (Y/N), return is boolean

< No need to pass in the prompt which include`? (Y/N)` when call the function

- `bool proceedNext(string message) `


## StatusContainer & User

Get the current user details

- `StatusContainer::currentUser.getXXX()`

Set the current user details

- `StatusContainer::currentUser.setXXX()`