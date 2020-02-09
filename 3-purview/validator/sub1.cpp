#include "common.h"
#include "bounds.h"

int main() {
    Checker c{}; c.validate();
    ensuref(c.DisZero && c.smallN, "Does not match sub1 bounds");
    return 0;
}
