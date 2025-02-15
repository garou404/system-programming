#include <stdlib.h>
#include <string.h>

char *message[] = {
    "Salut tout le monde!",
    "Hello World!"
};

int whatIsMyLanguage() {
    if (strcmp(getenv("LANG"), "en_US.UTF-8") == 0) {
        return 1;
    }else {
        return 0;
    }
}