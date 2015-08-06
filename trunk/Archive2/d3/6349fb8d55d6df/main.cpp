u128 mulmod_arcoth_binom(u128 a, u128 b, u128 m) {
    u128 ah = a >> 64, al = (u64)a;
	u128 bh = b >> 64, bl = (u64)b;
	u128 ahbh = ah*bh%m, ahbl = ah*bl%m, albh = al*bh%m;
	for (int i=0; i < 64; ++i) {
		ahbl = twiceBounded(ahbl,m);
		albh = twiceBounded(albh,m);
		ahbh = twiceBounded(ahbh,m);
		ahbh = twiceBounded(ahbh,m);
	}
	return addmodBounded(addmodBounded(ahbh, al*bl%m, m), addmodBounded(ahbl, albh, m), m);
}