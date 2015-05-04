/*
 *
 *  microdecode: Decode the microcode update package, available from
 *               Intel, in to a form you can use to patch your bios.
 *               This tool is in no way endorsed by Intel.
 *
 *  Get the latest microcode from here:
 *  http://downloadcenter.intel.com/Detail_Desc.aspx?ProductID=483&DwnldID=14303
 *
 *
 *  Copyright (C) 2008  Richard A Burton (richardaburton@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/

#include <stdio.h>

int main(int argc, char* argv[]) {

	FILE *in = NULL, *out = NULL;
	int ints[4], prev[4];
	char s[100];
	int state = 1;

	if (argc != 2) {
		printf("usage: %s <microcode-yyyymmdd.dat>\n", argv[0]);
		return 1;
	}

	in = fopen(argv[1], "r");
	if (!in) {
		printf("Failed to open file: %s\n", argv[1]);
		return 1;
	}

	while (!feof(in)) {
		fgets(s, 100, in);
		if (4 == sscanf(s, "%X,\t%X,\t%X,\t%X,", &ints[0], &ints[1], &ints[2], &ints[3])) {
			if (state == 1) {
				prev[0] = ints[0];
				prev[1] = ints[1];
				prev[2] = ints[2];
				prev[3] = ints[3];
				state = 2;
			} else if (state == 2) {
				sprintf(s, "cpu%08x_plat%08x_ver%08x_date%02x%02x%02x%02x.bin", prev[3], ints[2], prev[1],
					(prev[2] & 0x0000ff00)>>8, prev[2] & 0x000000ff, (prev[2] & 0xff000000)>>24, (prev[2] & 0x00ff0000)>>16);	
				printf("%s\n", s);
				out = fopen(s, "wb");
				fwrite(prev, sizeof(int), 4, out);
				fwrite(ints, sizeof(int), 4, out);
				state = 0;
			} else {
				fwrite(ints, sizeof(int), 4, out);
			}
		} else if (state != 1) {
			if (out) fclose(out);
			out = NULL;
			state = 1;
		}
	}

	if (out) fclose(out);
	if (in) fclose(in);

	return 0;
}
