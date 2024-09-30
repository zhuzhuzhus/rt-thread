#include "mdio.h"

rt_err_t rt_phy_device_register(struct rt_phy_dev *pdev)
{

}

rt_err_t rt_phy_driver_register(struct rt_phy_drv *pdrv)
{

}
const static struct rt_bus phy_bus
{
    .name = "phy",
    .match = rt_mdio_bus_match,
}; 