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


## Menu

Validate the input option is digit or in the range, return -1 means error

- `Menu::validOption(string input, int maxOption)`