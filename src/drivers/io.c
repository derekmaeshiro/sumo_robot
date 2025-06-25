#include "io.h"
#include "../common/defines.h"

void io_set_select(io_e io, io_select_e select)
{
    UNUSED(io);
    UNUSED(select);

    // TODO: implement
}

void io_set_direction(io_e io, io_dir_e direction)
{
    UNUSED(io);
    UNUSED(direction);
    // TODO: Implement
}

void io_set_resistor(io_e io, io_resistor_e resistor)
{
    UNUSED(io);
    UNUSED(resistor);
    // TODO: implement
}

void io_set_out(io_e io, io_out_e out)
{
    UNUSED(io);
    UNUSED(out);
    // TODO: implement
}

io_in_e io_get_input(io_e io)
{
    UNUSED(io);

    return 0;
    // TODO: implement
}
