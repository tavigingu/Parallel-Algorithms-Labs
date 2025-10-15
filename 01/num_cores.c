#include <unistd.h>

int main()
{
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    printf("num of processors:%ld\n", number_of_processors);

    return 0;
}

/*
_SC_PAGESIZE            Mărimea unei pagini de memorie în bytes (de obicei 4096 pe Linux).
_SC_PHYS_PAGES          Numărul total de pagini de memorie fizică disponibile în sistem.
_SC_NPROCESSORS_CONF    Numărul total de procesoare configurate în sistem (inclusiv offline).
_SC_OPEN_MAX            Numărul maxim de fișiere deschise simultan de un proces (minim 20 POSIX).
_SC_ARG_MAX             Lungimea maximă a argumentelor pentru funcții exec() (minim 4096 bytes).
_SC_CLK_TCK             "Numărul de ""ticks"" ale ceasului pe secundă (folosit pentru timere)."
_SC_VERSION             Versiunea standardului POSIX (ex: 199009L pentru revizia din sept. 1990).
_SC_SYMLOOP_MAX         Numărul maxim de link-uri simbolice în lanț înainte de eroare ELOOP (minim 8).
_SC_RE_DUP_MAX          Numărul maxim de repetări în expresii regulate (minim 255).
*/