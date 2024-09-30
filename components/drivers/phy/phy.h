#ifndef __NET_PHY_H__
#define __NET_PHY_H__
#include <net/ethernet.h>
#include <rtthread.h>
#include "mdio.h"
#include "ofw.h"
#define RT_PHY_MAX 32
struct rt_phy_device
{
    struct rt_device parent;
    struct mmi_bus *bus;
	struct rt_phy_driver *drv;
	rt_uint32_t    phy_id;
	rt_uint32_t    mmds;
	int            speed;
	int            duplex;

	int            link;
	int            port;
	rt_uint32_t    advertising;
	rt_uint32_t    supported;
	int            autoneg;
	int            pause;
	rt_ubase_t     addr;
	rt_bool_t      is_c45;

	rt_phy_interface interface;

#ifdef RT_USING_OFW
	struct rt_ofw_node *node;
#endif
	void          *priv;
};

struct rt_phy_driver
{
    struct rt_driver parent;
    char             name[RT_NAME_MAX];
    rt_uint64_t      uid;
    rt_uint64_t      mask;
    rt_uint64_t      mmds;

    rt_uint32_t      features;

    /* Will be called during phy_connect */
	int (*probe)(struct rt_phy_device *phydev);

	/* Called to configure the PHY, and modify the controller
	 * based on the results.  Should be called after phy_connect */
	int (*config)(struct rt_phy_device *phydev);

	/* Called when starting up the controller */
	int (*startup)(struct rt_phy_device *phydev);

	/* Called when bringing down the controller */
	int (*shutdown)(struct rt_phy_device *phydev);

	int (*read)(struct rt_phy_device *phydev, int addr, int devad, int reg);
	int (*write)(struct rt_phy_device *phydev, int addr, int devad, int reg,
			rt_uint16_t val);

	/* Phy specific driver override for reading a MMD register */
	int (*read_mmd)(struct rt_phy_device *phydev, int devad, int reg);

	/* Phy specific driver override for writing a MMD register */
	int (*write_mmd)(struct rt_phy_device *phydev, int devad, int reg,
			 rt_uint16_t val);

	/* driver private data */
	void *data;
};

#define RT_PHY_DEVICE_REGISTER(phy_dev)   \
static int rt_phy_device_register(void)   \
{                                         \
    rt_phy_device_register(&phy_dev);     \
    return 0;                             \
}                                         \
INIT_PREV_EXPORT(rt_phy_device_register); \

#define RT_PHY_DRIVER_REGISTER(phy_drv)   \
static int rt_phy_driver_register(void)   \
{                                         \
    rt_phy_driver_register(&phy_dev);     \
    return 0;                             \
}                                         \
INIT_PREV_EXPORT(rt_phy_device_register); \

#endif
