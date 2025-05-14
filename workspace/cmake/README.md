## Minimal configuration needed

Go to `CMakeLists.txt` at line `15`, and change path of avr-lib with the correct one for you.
Do the same for `avrdude configuration` inside `AvrToolChain.cmake` at line `10`.

## Add `compile_commands.json` to intellisense

Inside VScode press `Ctrl+Shift+p` and type `Open User Settings (JSON)` and add this new command:

````json
"C_Cpp.default.compileCommands": "build/compile_commands.json",
````

Then press `Ctrl+Shift+p` again and type `Reset IntelliSense Database`.
