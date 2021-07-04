/*
 * Copyright (c) 2019-2020 Kevin Townsend (KTOWN)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zsl/colorimetry.h>

/**
 * CIE 1931 2 Degree Standard Observer Color Matching Functions from 380 nm
 * to 830 nm in 5nm steps.
 *
 * @section Using the Color Matching Functions
 *
 * The calculation of CIE chromaticity coordinates for a given colored object
 * requires the multiplication of its spectral power at each wavelength times
 * the weighting factor from each of the three (X, Y, Z) color matching
 * functions. Summing these contributions gives three values called the
 * tristimulus values, from which the chromaticity coordinates are derived.
 *
 * For a visual representation of the color matching function see:
 * https://en.wikipedia.org/wiki/File:CIE_1931_XYZ_Color_Matching_Functions.svg
 */
static const struct zsl_clr_obs_data zsl_clr_obs_2_deg_data = {
	.observer = ZSL_CLR_OBS_2_DEG,
	.name = "CIE 1931 2 degree standard observer",
	.data = {
		{ 1.2990000E-04, 3.9200000E-06, 6.0610000E-04, },       /* 360 nm */
		{ 2.3210000E-04, 6.9700000E-06, 1.0860000E-03, },       /* 365 nm */
		{ 4.1490000E-04, 1.2390000E-05, 1.9460000E-03, },       /* 370 nm */
		{ 7.4160000E-04, 2.2020000E-05, 3.4860000E-03, },       /* 375 nm */
		{ 1.3680000E-03, 4.0000000E-05, 6.4500000E-04, },       /* 380 nm */
		{ 2.2360000E-03, 6.0000000E-05, 1.0550000E-02, },       /* 385 nm */
		{ 4.2430000E-03, 1.2000000E-04, 2.0050000E-02, },       /* 390 nm */
		{ 7.6500000E-03, 2.1700000E-04, 3.6210000E-02, },       /* 395 nm */
		{ 1.4310000E-02, 4.0000000E-04, 6.7850000E-02, },       /* 400 nm */
		{ 2.3190000E-02, 6.4000000E-04, 1.1020000E-01, },       /* 405 nm */
		{ 4.3510000E-02, 1.2100000E-03, 2.0740000E-01, },       /* 410 nm */
		{ 7.7630000E-02, 2.1800000E-03, 3.7130000E-01, },       /* 415 nm */
		{ 1.3438000E-01, 4.0000000E-03, 6.4560000E-01, },       /* 420 nm */
		{ 2.1477000E-01, 7.3000000E-03, 1.0390500E+00, },       /* 425 nm */
		{ 2.8390000E-01, 1.1600000E-02, 1.3856000E+00, },       /* 430 nm */
		{ 3.2850000E-01, 1.6840000E-02, 1.6229600E+00, },       /* 435 nm */
		{ 3.4828000E-01, 2.3000000E-02, 1.7470600E+00, },       /* 440 nm */
		{ 3.4806000E-01, 2.9800000E-02, 1.7826000E+00, },       /* 445 nm */
		{ 3.3620000E-01, 3.8000000E-02, 1.7721100E+00, },       /* 450 nm */
		{ 3.1870000E-01, 4.8000000E-02, 1.7441000E+00, },       /* 455 nm */
		{ 2.9080000E-01, 6.0000000E-02, 1.6692000E+00, },       /* 460 nm */
		{ 2.5110000E-01, 7.3900000E-02, 1.5281000E+00, },       /* 465 nm */
		{ 1.9536000E-01, 9.0980000E-02, 1.2876400E+00, },       /* 470 nm */
		{ 1.4210000E-01, 1.1260000E-01, 1.0419000E+00, },       /* 475 nm */
		{ 9.5640000E-02, 1.3902000E-01, 8.1295000E-01, },       /* 480 nm */
		{ 5.7950000E-02, 1.6930000E-01, 6.1620000E-01, },       /* 485 nm */
		{ 3.2010000E-02, 2.0802000E-01, 4.6518000E-01, },       /* 490 nm */
		{ 1.4700000E-02, 2.5860000E-01, 3.5330000E-01, },       /* 495 nm */
		{ 4.9000000E-03, 3.2300000E-01, 2.7200000E-01, },       /* 500 nm */
		{ 2.4000000E-03, 4.0730000E-01, 2.1230000E-01, },       /* 505 nm */
		{ 9.3000000E-03, 5.0300000E-01, 1.5820000E-01, },       /* 510 nm */
		{ 2.9100000E-02, 6.0820000E-01, 1.1170000E-01, },       /* 515 nm */
		{ 6.3270000E-02, 7.1000000E-01, 7.8250000E-02, },       /* 520 nm */
		{ 1.0960000E-01, 7.9320000E-01, 5.7250000E-02, },       /* 525 nm */
		{ 1.6550000E-01, 8.6200000E-01, 4.2160000E-02, },       /* 530 nm */
		{ 2.2575000E-01, 9.1485000E-01, 2.9840000E-02, },       /* 535 nm */
		{ 2.9040000E-01, 9.5400000E-01, 2.0300000E-02, },       /* 540 nm */
		{ 3.5970000E-01, 9.8030000E-01, 1.3400000E-02, },       /* 545 nm */
		{ 4.3345000E-01, 9.9495000E-01, 8.7500000E-03, },       /* 550 nm */
		{ 5.1205000E-01, 1.0000000E+00, 5.7500000E-03, },       /* 555 nm */
		{ 5.9450000E-01, 9.9500000E-01, 3.9000000E-03, },       /* 560 nm */
		{ 6.7840000E-01, 9.7860000E-01, 2.7500000E-03, },       /* 565 nm */
		{ 7.6210000E-01, 9.5200000E-01, 2.1000000E-03, },       /* 570 nm */
		{ 8.4250000E-01, 9.1540000E-01, 1.8000000E-03, },       /* 575 nm */
		{ 9.1630000E-01, 8.7000000E-01, 1.6500000E-03, },       /* 580 nm */
		{ 9.7860000E-01, 8.1630000E-01, 1.4000000E-03, },       /* 585 nm */
		{ 1.0263000E+00, 7.5700000E-01, 1.1000000E-03, },       /* 590 nm */
		{ 1.0567000E+00, 6.9490000E-01, 1.0000000E-03, },       /* 595 nm */
		{ 1.0622000E+00, 6.3100000E-01, 8.0000000E-04, },       /* 600 nm */
		{ 1.0456000E+00, 5.6680000E-01, 6.0000000E-04, },       /* 605 nm */
		{ 1.0026000E+00, 5.0300000E-01, 3.4000000E-04, },       /* 610 nm */
		{ 9.3840000E-01, 4.4120000E-01, 2.4000000E-04, },       /* 615 nm */
		{ 8.5450000E-01, 3.8100000E-01, 1.9000000E-04, },       /* 620 nm */
		{ 7.5140000E-01, 3.2100000E-01, 1.0000000E-04, },       /* 625 nm */
		{ 6.4240000E-01, 2.6500000E-01, 5.0000000E-04, },       /* 630 nm */
		{ 5.4190000E-01, 2.1700000E-01, 3.0000000E-04, },       /* 635 nm */
		{ 4.4790000E-01, 1.7500000E-01, 2.0000000E-04, },       /* 640 nm */
		{ 3.6080000E-01, 1.3800000E-01, 1.0000000E-04, },       /* 645 nm */
		{ 2.8350000E-01, 1.0700000E-01, 0.0000000E+00, },       /* 650 nm */
		{ 2.1870000E-01, 8.1600000E-02, 0.0000000E+00, },       /* 655 nm */
		{ 1.6490000E-01, 6.1000000E-02, 0.0000000E+00, },       /* 660 nm */
		{ 1.2120000E-01, 4.4580000E-02, 0.0000000E+00, },       /* 665 nm */
		{ 8.7400000E-02, 3.2000000E-02, 0.0000000E+00, },       /* 670 nm */
		{ 6.3600000E-02, 2.3200000E-02, 0.0000000E+00, },       /* 675 nm */
		{ 4.6770000E-02, 1.7000000E-02, 0.0000000E+00, },       /* 680 nm */
		{ 3.2900000E-02, 1.1920000E-02, 0.0000000E+00, },       /* 685 nm */
		{ 2.2700000E-02, 8.2100000E-03, 0.0000000E+00, },       /* 690 nm */
		{ 1.5840000E-02, 5.7230000E-03, 0.0000000E+00, },       /* 695 nm */
		{ 1.1359000E-02, 4.1020000E-03, 0.0000000E+00, },       /* 700 nm */
		{ 8.1110000E-03, 2.9290000E-03, 0.0000000E+00, },       /* 705 nm */
		{ 5.7900000E-03, 2.0910000E-03, 0.0000000E+00, },       /* 710 nm */
		{ 4.1090000E-03, 1.4840000E-03, 0.0000000E+00, },       /* 715 nm */
		{ 2.8990000E-03, 1.0470000E-03, 0.0000000E+00, },       /* 720 nm */
		{ 2.0490000E-03, 7.4000000E-04, 0.0000000E+00, },       /* 725 nm */
		{ 1.4400000E-03, 5.2000000E-04, 0.0000000E+00, },       /* 730 nm */
		{ 1.0000000E-03, 3.6100000E-04, 0.0000000E+00, },       /* 735 nm */
		{ 6.9000000E-04, 2.4900000E-04, 0.0000000E+00, },       /* 740 nm */
		{ 4.7600000E-04, 1.7190000E-04, 0.0000000E+00, },       /* 745 nm */
		{ 3.3200000E-04, 1.2000000E-04, 0.0000000E+00, },       /* 750 nm */
		{ 2.3500000E-04, 8.4800000E-05, 0.0000000E+00, },       /* 755 nm */
		{ 1.6600000E-04, 6.0000000E-05, 0.0000000E+00, },       /* 760 nm */
		{ 1.7700000E-04, 4.2400000E-05, 0.0000000E+00, },       /* 765 nm */
		{ 8.3000000E-05, 3.0000000E-05, 0.0000000E+00, },       /* 770 nm */
		{ 5.9000000E-05, 2.1000000E-05, 0.0000000E+00, },       /* 775 nm */
		{ 4.2000000E-05, 1.5000000E-05, 0.0000000E+00, },       /* 780 nm */
		{ 2.9350000E-05, 1.0600000E-05, 0.0000000E+00, },       /* 785 nm */
		{ 2.0670000E-05, 7.4700000E-06, 0.0000000E+00, },       /* 790 nm */
		{ 1.4560000E-05, 5.2600000E-06, 0.0000000E+00, },       /* 795 nm */
		{ 1.0250000E-05, 3.7000000E-06, 0.0000000E+00, },       /* 800 nm */
		{ 7.2200000E-06, 2.6100000E-06, 0.0000000E+00, },       /* 805 nm */
		{ 5.0900000E-06, 1.8400000E-06, 0.0000000E+00, },       /* 810 nm */
		{ 3.5800000E-06, 1.2900000E-06, 0.0000000E+00, },       /* 815 nm */
		{ 2.5200000E-06, 9.1000000E-07, 0.0000000E+00, },       /* 820 nm */
		{ 1.7800000E-06, 6.4000000E-07, 0.0000000E+00, },       /* 825 nm */
		{ 1.2500000E-06, 4.5000000E-07, 0.0000000E+00, }        /* 830 nm */
	}
};

/**
 * CIE 1964 10 degree supplementary standard observer color matching functions
 * from 380 nm to 830 nm in 5nm steps.
 */
static const struct zsl_clr_obs_data zsl_clr_obs_10_deg_data = {
	.observer = ZSL_CLR_OBS_10_DEG,
	.name = "CIE 1964 10 degree standard observer",
	.data = {
		{ 0.000000122200, 0.000000013398, 0.000000535027 },     /* 360 nm */
		{ 0.000000919270, 0.000000100650, 0.000004028300 },     /* 365 nm */
		{ 0.000005958600, 0.000000651100, 0.000026143700 },     /* 370 nm */
		{ 0.000033266000, 0.000003625000, 0.000146220000 },     /* 375 nm */
		{ 0.000159952000, 0.000017364000, 0.000704776000 },     /* 380 nm */
		{ 0.000662440000, 0.000071560000, 0.002927800000 },     /* 385 nm */
		{ 0.002361600000, 0.000253400000, 0.010482200000 },     /* 390 nm */
		{ 0.007242300000, 0.000768500000, 0.032344000000 },     /* 395 nm */
		{ 0.019109700000, 0.002004400000, 0.086010900000 },     /* 400 nm */
		{ 0.043400000000, 0.004509000000, 0.197120000000 },     /* 405 nm */
		{ 0.084736000000, 0.008756000000, 0.389366000000 },     /* 410 nm */
		{ 0.140638000000, 0.014456000000, 0.656760000000 },     /* 415 nm */
		{ 0.204492000000, 0.021391000000, 0.972542000000 },     /* 420 nm */
		{ 0.264737000000, 0.029497000000, 1.282500000000 },     /* 425 nm */
		{ 0.314679000000, 0.038676000000, 1.553480000000 },     /* 430 nm */
		{ 0.357719000000, 0.049602000000, 1.798500000000 },     /* 435 nm */
		{ 0.383734000000, 0.062077000000, 1.967280000000 },     /* 440 nm */
		{ 0.386726000000, 0.074704000000, 2.027300000000 },     /* 445 nm */
		{ 0.370702000000, 0.089456000000, 1.994800000000 },     /* 450 nm */
		{ 0.342957000000, 0.106256000000, 1.900700000000 },     /* 455 nm */
		{ 0.302273000000, 0.128201000000, 1.745370000000 },     /* 460 nm */
		{ 0.254085000000, 0.152761000000, 1.554900000000 },     /* 465 nm */
		{ 0.195618000000, 0.185190000000, 1.317560000000 },     /* 470 nm */
		{ 0.132349000000, 0.219940000000, 1.030200000000 },     /* 475 nm */
		{ 0.080507000000, 0.253589000000, 0.772125000000 },     /* 480 nm */
		{ 0.041072000000, 0.297665000000, 0.570060000000 },     /* 485 nm */
		{ 0.016172000000, 0.339133000000, 0.415254000000 },     /* 490 nm */
		{ 0.005132000000, 0.395379000000, 0.302356000000 },     /* 495 nm */
		{ 0.003816000000, 0.460777000000, 0.218502000000 },     /* 500 nm */
		{ 0.015444000000, 0.531360000000, 0.159249000000 },     /* 505 nm */
		{ 0.037465000000, 0.606741000000, 0.112044000000 },     /* 510 nm */
		{ 0.071358000000, 0.685660000000, 0.082248000000 },     /* 515 nm */
		{ 0.117749000000, 0.761757000000, 0.060709000000 },     /* 520 nm */
		{ 0.172953000000, 0.823330000000, 0.043050000000 },     /* 525 nm */
		{ 0.236491000000, 0.875211000000, 0.030451000000 },     /* 530 nm */
		{ 0.304213000000, 0.923810000000, 0.020584000000 },     /* 535 nm */
		{ 0.376772000000, 0.961988000000, 0.013676000000 },     /* 540 nm */
		{ 0.451584000000, 0.982200000000, 0.007918000000 },     /* 545 nm */
		{ 0.529826000000, 0.991761000000, 0.003988000000 },     /* 550 nm */
		{ 0.616053000000, 0.999110000000, 0.001091000000 },     /* 555 nm */
		{ 0.705224000000, 0.997340000000, 0.000000000000 },     /* 560 nm */
		{ 0.793832000000, 0.982380000000, 0.000000000000 },     /* 565 nm */
		{ 0.878655000000, 0.955552000000, 0.000000000000 },     /* 570 nm */
		{ 0.951162000000, 0.915175000000, 0.000000000000 },     /* 575 nm */
		{ 1.014160000000, 0.868934000000, 0.000000000000 },     /* 580 nm */
		{ 1.074300000000, 0.825623000000, 0.000000000000 },     /* 585 nm */
		{ 1.118520000000, 0.777405000000, 0.000000000000 },     /* 590 nm */
		{ 1.134300000000, 0.720353000000, 0.000000000000 },     /* 595 nm */
		{ 1.123990000000, 0.658341000000, 0.000000000000 },     /* 600 nm */
		{ 1.089100000000, 0.593878000000, 0.000000000000 },     /* 605 nm */
		{ 1.030480000000, 0.527963000000, 0.000000000000 },     /* 610 nm */
		{ 0.950740000000, 0.461834000000, 0.000000000000 },     /* 615 nm */
		{ 0.856297000000, 0.398057000000, 0.000000000000 },     /* 620 nm */
		{ 0.754930000000, 0.339554000000, 0.000000000000 },     /* 625 nm */
		{ 0.647467000000, 0.283493000000, 0.000000000000 },     /* 630 nm */
		{ 0.535110000000, 0.228254000000, 0.000000000000 },     /* 635 nm */
		{ 0.431567000000, 0.179828000000, 0.000000000000 },     /* 640 nm */
		{ 0.343690000000, 0.140211000000, 0.000000000000 },     /* 645 nm */
		{ 0.268329000000, 0.107633000000, 0.000000000000 },     /* 650 nm */
		{ 0.204300000000, 0.081187000000, 0.000000000000 },     /* 655 nm */
		{ 0.152568000000, 0.060281000000, 0.000000000000 },     /* 660 nm */
		{ 0.112210000000, 0.044096000000, 0.000000000000 },     /* 665 nm */
		{ 0.081260600000, 0.031800400000, 0.000000000000 },     /* 670 nm */
		{ 0.057930000000, 0.022601700000, 0.000000000000 },     /* 675 nm */
		{ 0.040850800000, 0.015905100000, 0.000000000000 },     /* 680 nm */
		{ 0.028623000000, 0.011130300000, 0.000000000000 },     /* 685 nm */
		{ 0.019941300000, 0.007748800000, 0.000000000000 },     /* 690 nm */
		{ 0.013842000000, 0.005375100000, 0.000000000000 },     /* 695 nm */
		{ 0.009576880000, 0.003717740000, 0.000000000000 },     /* 700 nm */
		{ 0.006605200000, 0.002564560000, 0.000000000000 },     /* 705 nm */
		{ 0.004552630000, 0.001768470000, 0.000000000000 },     /* 710 nm */
		{ 0.003144700000, 0.001222390000, 0.000000000000 },     /* 715 nm */
		{ 0.002174960000, 0.000846190000, 0.000000000000 },     /* 720 nm */
		{ 0.001505700000, 0.000586440000, 0.000000000000 },     /* 725 nm */
		{ 0.001044760000, 0.000407410000, 0.000000000000 },     /* 730 nm */
		{ 0.000727450000, 0.000284041000, 0.000000000000 },     /* 735 nm */
		{ 0.000508258000, 0.000198730000, 0.000000000000 },     /* 740 nm */
		{ 0.000356380000, 0.000139550000, 0.000000000000 },     /* 745 nm */
		{ 0.000250969000, 0.000098428000, 0.000000000000 },     /* 750 nm */
		{ 0.000177730000, 0.000069819000, 0.000000000000 },     /* 755 nm */
		{ 0.000126390000, 0.000049737000, 0.000000000000 },     /* 760 nm */
		{ 0.000090151000, 0.000035540500, 0.000000000000 },     /* 765 nm */
		{ 0.000064525800, 0.000025486000, 0.000000000000 },     /* 770 nm */
		{ 0.000046339000, 0.000018338400, 0.000000000000 },     /* 775 nm */
		{ 0.000033411700, 0.000013249000, 0.000000000000 },     /* 780 nm */
		{ 0.000024209000, 0.000009619600, 0.000000000000 },     /* 785 nm */
		{ 0.000017611500, 0.000007012800, 0.000000000000 },     /* 790 nm */
		{ 0.000012855000, 0.000005129800, 0.000000000000 },     /* 795 nm */
		{ 0.000009413630, 0.000003764730, 0.000000000000 },     /* 800 nm */
		{ 0.000006913000, 0.000002770810, 0.000000000000 },     /* 805 nm */
		{ 0.000005093470, 0.000002046130, 0.000000000000 },     /* 810 nm */
		{ 0.000003767100, 0.000001516770, 0.000000000000 },     /* 815 nm */
		{ 0.000002795310, 0.000001128090, 0.000000000000 },     /* 820 nm */
		{ 0.000002082000, 0.000000842160, 0.000000000000 },     /* 825 nm */
		{ 0.000001553140, 0.000000629700, 0.000000000000 }      /* 830 nm */
		}
	};

	void
	zsl_clr_obs_get(enum zsl_clr_obs obs, const struct zsl_clr_obs_data **data)
	{
		switch (obs) {
		case ZSL_CLR_OBS_10_DEG:
			*data = &zsl_clr_obs_10_deg_data;
			break;
		case ZSL_CLR_OBS_2_DEG:
			*data = &zsl_clr_obs_2_deg_data;
			break;
		}
	}
