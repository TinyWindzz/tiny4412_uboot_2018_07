/*
 * Clock Initialization for board based on EXYNOS4210
 *
 * Copyright (C) 2013 Samsung Electronics
 * Rajeshwari Shinde <rajeshwari.s@samsung.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <config.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clk.h>
#include <asm/arch/clock.h>
#include "common_setup.h"
#include "exynos4_setup.h"

/*
 * system_clock_init: Initialize core clock and bus clock.
 * void system_clock_init(void)
 */
void system_clock_init(void)
{
	struct exynos4x12_clock *clk =
			(struct exynos4x12_clock *)samsung_get_base_clock();

	/* APLL= 1400 MHz MPLL=800 MHz */

	writel(0x01000001, &clk->src_cpu);

	sdelay(0x10000);

	writel(0x66666, &clk->src_peril0);
	writel(0x10, &clk->src_leftbus);
	writel(0x10, &clk->src_rightbus);
	writel(0x110, &clk->src_top0);
	writel(0x1111000, &clk->src_top1);
	writel(0x00011000, &clk->src_dmc);

	sdelay(0x10000);

	writel(0x1160730, &clk->div_cpu0);
	writel(0x506, &clk->div_cpu1);
	writel(0x111113, &clk->div_dmc0);
	writel(0x1011713, &clk->div_dmc1);
	writel(0xfffff, &clk->div_peril0);
	writel(0x1070107, &clk->div_fsys1);
	writel(0x4070047, &clk->div_fsys2);
	writel(0x7, &clk->div_fsys3);

	/* Set PLL locktime */
	writel(PLL_LOCKTIME, &clk->apll_lock);
	writel(PLL_LOCKTIME, &clk->mpll_lock);

	writel(0x803800, &clk->apll_con1);
	writel(0x80af0300, &clk->apll_con0);
	writel(0x803800, &clk->mpll_con1);
	writel(0x80640300, &clk->mpll_con0);

	sdelay(0x30000);
}
