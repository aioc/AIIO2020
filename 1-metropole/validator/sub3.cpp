#include "common.h"
#include "bounds.h"

int main() {
    Checker c{}; c.validate();
    ensuref(c.allCostOne, "Does not match sub3 bounds");
    return 0;
}
