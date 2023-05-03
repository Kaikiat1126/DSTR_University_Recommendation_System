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

Get user input's university name, return string 

- `string searchUniByName()`


## StatusContainer & User

Get the current user details

- `StatusContainer::currentUser.getXXX()`

Set the current user details

- `StatusContainer::currentUser.setXXX()`

Get the User List (Linkedlist)

- `StatusContainer::userList()`

Ge the University List (Linkedlist)

- `StatusContainer::universityList`


## Struture

Define a University's structure

- `struct UniversityStruct`

Define a University's Node

- `struct UniversityNode`

Define a User's structure

- `struct UserStruct`

Define a User's Node

- `struct UserNode`


## University List

Create a new node on university linkedlist

- `UniversityNode* createNewNode(UniversityStruct university)`

Insert a new node to the end of University Linkedlist

- `void insertToEndOfList(UniversityStruct university)`

Search the university by rank, return a University Node

- `UniversityNode* searchByRank(int rank)`

Search the university by institution, return a University Node

- `UniversityNode* searchByInstitution(std::string institution);`

Display the university list

- `void displayUniversityList()`


## IsVector 

< Self implement vector structure

Define a vector

- `IsVector<type> vector`

Insert value into vector

- `vector.insert(int index, T element)`

Push back value into vector

- `vector.push_back(T element)`

Get vector's size

- `vector.getSize()`

Clear vector

- `vector.clear()`


## IsUnorderedMap

< Self implement unordered_map structure

Define a unordered_map

- `IsUnorderedMap<type, type, size> map`

Insert key, value into unordered map

- `map.insert(KeyType key, ValueType value)`

Get unordered map's size

- `map.getSize()`

Remove value from unordered map by key

- `map.remove(KeyType key)`

Get value by key

- `map.getValue(KeyType key)`

Get value by index

- `map.getValue(int index)`

Get key by value

- `map.getKey(ValueType value)`

Get key by index

- `map.getKey(int index)`


## Visitor

Display all university list

- `void displayAllUniversity()`

Let user select with search algorithm to be used (Landing Search Universtiy)

- `void chooseSearchAlgo()`

Let user select with sort algorithm to be used (Landing Sort Universtiy)

- `void chooseSortAlgo()`


## Timer

Used to get current time or function's start/end time, return auto time

- `auto getCurrentTime()`

Used to calculate the function's run time, return string

- `string getRunTime(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end)`
