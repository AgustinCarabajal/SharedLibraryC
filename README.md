# Shared Library in the C PL

- Installation

> git clone https://github.com/AgustinCarabajal/SharedLibraryC.git
>
> cd SharedLibraryC && cd chantas
>
> sudo make install

- Usage

> Add #include <chantas/FILE_NAME> in your main.c file
>
> Compile with the flag -lchantas

Also you can add libraries into the /chantas folder and run the following command

> sudo make update

### Running Valgrind for memory leaking

> valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main
