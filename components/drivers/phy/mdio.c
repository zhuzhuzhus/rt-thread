#include "mdio.h"

static struct rt_list_node mdio_list;


static int mdio_init(void)
{
    rt_list_init(&mdio_list);
}
INIT_CORE_EXPORT(mdio_init)