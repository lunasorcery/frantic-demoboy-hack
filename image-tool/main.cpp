#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

struct block_t {
	uint8_t bytes[16];
};

block_t encodeBlock(uint8_t* image, int bx, int by) {
	block_t b;
	memset(b.bytes, 0, 16);
	for(int y=0;y<8;++y){
		for(int x=0;x<8;++x){
			uint8_t v = image[(by*8+y)*160+bx*8+x];
			b.bytes[y*2+0] |= ((v&0x40)<<1)>>x;
			b.bytes[y*2+1] |= (v&0x80)>>x;
		}
	}
	return b;
}

block_t cache[256];
int cacheSize=0;

uint8_t getCacheIndex(block_t block) {
	for(int i=0;i<cacheSize;++i) {
		if (memcmp(&cache[i], &block, sizeof(block_t)) == 0) {
			return i;
		}
	}
	cache[cacheSize] = block;
	cacheSize++;
	return cacheSize-1;
}

int main() {
	int w,h,n;
	unsigned char *data = stbi_load("logo.png", &w, &h, &n, 1);
	if (data)
	{
		uint8_t indexMap[20*18];
		for(int by=0;by<18;++by) {
			for(int bx=0;bx<20;++bx) {
				block_t curblock = encodeBlock(data, bx, by);
				indexMap[by*20+bx] = getCacheIndex(curblock);
			}
		}

		printf("const unsigned char bkg_tiles[]={\n");
		for(int i=0;i<cacheSize;++i) {
			printf("//cache entry %d:\n", i);
			for(int j=0;j<16;++j) {
				printf("0x%02x, ", cache[i].bytes[j]);
			}
			printf("\n");
		}
		printf("};\n");

		printf("const unsigned char bkg_tiles_count = %d;\n", cacheSize);

		printf("const unsigned char bkg_index_map[]={\n");
		printf("// index map:\n");
		for(int y=0;y<18;++y) {
			for(int x=0;x<20;++x) {
				printf("%d, ", indexMap[y*20+x]);
			}
			printf("\n");
		}
		printf("};\n");

		stbi_image_free(data);
	}
}