#include "common.h"
#include "bounds.h"

int main() {
    Checker c{}; c.validate();
    ensuref(c.DisZero, "Does not match sub2 bounds");
    return 0;
}
