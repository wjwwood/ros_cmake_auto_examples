Each of the folders here contain a single example package.
All of the examples consist of three files, a `package.xml`, a `CMakeLists.txt`, and a single C++ source file.

- `empty_node`:
  - This example just contains a custom, but empty node class.
- `node_with_publisher`:
  - This example contains a custom node class which contains a publisher and timer and periodically publishes a string to the "chatter" topic.
- `node_with_subscription`:
  - This example contains a custom node class which contains a subscription on the topic "chatter" and prints the string it receives for each message.
