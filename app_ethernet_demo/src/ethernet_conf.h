// Copyright (c) 2011, XMOS Ltd, All rights reserved
// This software is freely distributable under a derivative of the
// University of Illinois/NCSA Open Source License posted in
// LICENSE.txt and at <http://github.xcore.com/>

#ifdef CONFIG_FULL

#define ETHERNET_USE_FULL 1

#define ETHERNET_USE_LITE 1

#define MAX_ETHERNET_PACKET_SIZE (1518)

#define MAX_ETHERNET_CLIENTS   (4)    

#else

#define ETHERNET_USE_LITE 1

#endif



