# My logger
added a simple and conveniet logging interface to imgui. log function takes a string and a level as a parameter and logs it. It can also optionally take a custom seperator between lines. Default is "\n".

Added helper functions that allow one to easily turn various integral and floating types to strings of different type to be logged using log function. Includes regular, binary, scientific, and floating precision reprerentations.

Added GUI console to which everything is logged. It is color coded based on log level. Allows you to customize what log levels you want to see as well as clear console and enable/disable cout/file logging.
