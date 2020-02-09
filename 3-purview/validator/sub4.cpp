#include "common.h"
#include "bounds.h"

int main() {
    Checker c{}; c.validate();
    ensuref(c.demolishedInOrder, "Does not match sub4 bounds");
    return 0;
}
