#include "../include/assert.hpp"

int main(){

    CPP_UNIT_ASSERT cua;

    cua.assert_equals("oi", "slc");
    cua.assert_equals("oi", "epa");
    cua.assert_equals("oi", "oi");

    return 0;
}