#ifndef __GB16_h
#define __GB16_h

// ------------------  汉字字模的数据结构定义 ------------------------ //
struct  typFNT_GB16                 // 汉字字模数据结构
{
	unsigned char  Index[3];               // 汉字内码索引
	unsigned char   Msk[32];                        // 点阵码数据
};

/////////////////////////////////////////////////////////////////////////
// 汉字字模表                                                          //
// 汉字库: 宋体16.dot,横向取模左高位,数据排列:从左到右从上到下         //
/////////////////////////////////////////////////////////////////////////
const struct  typFNT_GB16 codeGB_16[] =          // 数据表
{

	/*--  文字:  硕  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"硕",0x00,0x00,0x7D,0xFE,0x10,0x20,0x10,0x40,0x21,0xFC,0x21,0x04,0x3D,0x24,0x65,0x24,
	0xA5,0x24,0x25,0x24,0x25,0x24,0x3D,0x50,0x24,0x48,0x20,0x84,0x01,0x06,0x06,0x02,

	/*--  文字:  耀  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"耀",0x13,0xDC,0x12,0x44,0x95,0x54,0x54,0xCC,0x11,0x54,0xFE,0xC4,0x29,0x20,0x29,0xFC,
	0x2B,0x20,0x2D,0xFC,0x29,0x20,0x2B,0xFC,0x5D,0x20,0x49,0x20,0x81,0xFE,0x01,0x00,

	/*--  文字:  电  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"电",0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,
	0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x02,0x01,0x02,0x00,0xFE,0x00,0x00,

	/*--  文字:  子  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"子",0x00,0x00,0x3F,0xF0,0x00,0x20,0x00,0x40,0x00,0x80,0x01,0x00,0x01,0x00,0x01,0x04,
	0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00,

	/*--  文字:  科  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"科",0x06,0x08,0x78,0x88,0x08,0x48,0x08,0x48,0xFE,0x08,0x18,0x88,0x1C,0x48,0x2A,0x48,
	0x28,0x0E,0x48,0x78,0x8B,0x88,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,

	/*--  文字:  技  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"技",0x10,0x20,0x10,0x20,0x10,0x20,0xFD,0xFE,0x10,0x20,0x14,0x20,0x19,0xFC,0x31,0x08,
	0xD0,0x88,0x10,0x90,0x10,0x60,0x10,0x60,0x10,0x90,0x11,0x0E,0x56,0x04,0x20,0x00,

	/*--  文字:  有  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"有",0x01,0x00,0x01,0x00,0x7F,0xFE,0x02,0x00,0x04,0x00,0x0F,0xF0,0x18,0x10,0x28,0x10,
	0x4F,0xF0,0x88,0x10,0x08,0x10,0x0F,0xF0,0x08,0x10,0x08,0x90,0x08,0x70,0x08,0x20,

	/*--  文字:  限  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"限",0x00,0x00,0xFB,0xF8,0x92,0x08,0x93,0xF8,0xA2,0x08,0xA2,0x08,0x93,0xF8,0x8A,0x80,
	0x8A,0x48,0xAA,0x50,0x92,0x20,0x82,0x20,0x82,0x10,0x82,0x8E,0x83,0x04,0x82,0x00,

	/*--  文字:  公  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"公",0x00,0x00,0x04,0x40,0x06,0x40,0x04,0x40,0x08,0x20,0x08,0x10,0x10,0x18,0x22,0x0E,
	0x43,0x04,0x02,0x00,0x04,0x20,0x08,0x10,0x11,0xF8,0x3F,0x18,0x10,0x10,0x00,0x00,

	/*--  文字:  司  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"司",0x00,0x00,0x3F,0xFC,0x00,0x04,0x00,0x04,0x7F,0xE4,0x00,0x04,0x00,0x04,0x3F,0xC4,
	0x20,0x44,0x20,0x44,0x3F,0xC4,0x20,0x44,0x20,0x04,0x00,0x14,0x00,0x08,0x00,0x00,

	/*--  文字:  专  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"专",0x01,0x00,0x01,0x00,0x3F,0xF8,0x02,0x00,0x02,0x00,0xFF,0xFE,0x04,0x00,0x08,0x20,
	0x0F,0xF0,0x00,0x20,0x00,0x40,0x02,0x80,0x01,0x00,0x00,0x80,0x00,0x40,0x00,0x00,

	/*--  文字:  业  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"业",0x04,0x40,0x04,0x40,0x04,0x40,0x04,0x44,0x44,0x46,0x24,0x4C,0x24,0x48,0x14,0x50,
	0x1C,0x50,0x14,0x60,0x04,0x40,0x04,0x40,0x04,0x44,0xFF,0xFE,0x00,0x00,0x00,0x00,

	/*--  文字:  开  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"开",0x00,0x00,0x7F,0xFE,0x04,0x20,0x04,0x20,0x04,0x20,0x04,0x20,0xFF,0xFE,0x04,0x20,
	0x04,0x20,0x04,0x20,0x08,0x20,0x08,0x20,0x10,0x20,0x20,0x20,0x40,0x20,0x00,0x00,

	/*--  文字:  发  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"发",0x02,0x00,0x22,0x40,0x22,0x30,0x22,0x10,0x7F,0xFE,0x24,0x00,0x04,0x00,0x07,0xE0,
	0x0C,0x20,0x0A,0x20,0x0A,0x20,0x11,0x40,0x20,0x80,0x41,0x60,0x86,0x1C,0x18,0x08,

	/*--  文字:  板  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"板",0x10,0x1C,0x11,0xE0,0x11,0x00,0x11,0x00,0xFD,0x00,0x11,0xFC,0x39,0x84,0x35,0x48,
	0x55,0x48,0x52,0x30,0x92,0x10,0x12,0x30,0x14,0x48,0x10,0x8E,0x11,0x04,0x00,0x00,

	/*--  文字:  工  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"工",0x00,0x00,0x3F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,

	/*--  文字:  控  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"控",0x10,0x00,0x10,0x20,0x10,0x10,0xFD,0xFE,0x11,0x04,0x10,0x50,0x14,0x8C,0x19,0x04,
	0x30,0x00,0xD1,0xFC,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x53,0xFE,0x20,0x00,

	/*--  文字:  设  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"设",0x40,0x00,0x21,0xF0,0x31,0x10,0x21,0x10,0x01,0x10,0x01,0x10,0xE2,0x0E,0x25,0xF8,
	0x21,0x08,0x21,0x08,0x20,0x90,0x20,0x90,0x28,0x60,0x30,0x90,0x23,0x0E,0x0C,0x04,

	/*--  文字:  备  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"备",0x08,0x00,0x0F,0xF0,0x08,0x20,0x14,0x20,0x22,0x40,0x41,0x80,0x02,0x40,0x0C,0x30,
	0x30,0x1E,0xDF,0xF4,0x11,0x10,0x1F,0xF0,0x11,0x10,0x11,0x10,0x1F,0xF0,0x10,0x10,

	/*--  文字:  技  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"技",0x10,0x20,0x10,0x20,0x10,0x20,0xFD,0xFE,0x10,0x20,0x14,0x20,0x19,0xFC,0x31,0x08,
	0xD0,0x88,0x10,0x90,0x10,0x60,0x10,0x60,0x10,0x90,0x11,0x0E,0x56,0x04,0x20,0x00,

	/*--  文字:  术  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"术",0x01,0x00,0x01,0x20,0x01,0x10,0x01,0x00,0xFF,0xFE,0x01,0x00,0x03,0x80,0x05,0x40,
	0x05,0x20,0x09,0x10,0x11,0x18,0x21,0x0E,0xC1,0x04,0x01,0x00,0x01,0x00,0x00,0x00,

	/*--  文字:  支  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"支",0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFE,0x01,0x00,0x01,0x00,0x1F,0xF8,0x08,0x10,
	0x04,0x20,0x04,0x20,0x02,0x40,0x01,0x80,0x02,0x40,0x0C,0x30,0x70,0x0E,0x00,0x04,

	/*--  文字:  持  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"持",0x10,0x40,0x10,0x40,0x13,0xFC,0xFC,0x40,0x10,0x40,0x17,0xFE,0x14,0x10,0x18,0x10,
	0x37,0xFE,0xD0,0x10,0x11,0x10,0x10,0xD0,0x10,0x90,0x10,0x10,0x50,0x50,0x20,0x20,

	/*--  文字:  论  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"论",0x40,0x40,0x20,0x40,0x30,0xA0,0x20,0x90,0x01,0x08,0x02,0x06,0xE5,0x04,0x21,0x10,
	0x21,0x38,0x21,0xC0,0x21,0x00,0x25,0x00,0x29,0x04,0x31,0x04,0x20,0xFC,0x00,0x00,

	/*--  文字:  坛  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	"坛",0x00,0x00,0x11,0xFC,0x10,0x00,0x10,0x00,0x10,0x00,0xFC,0x00,0x13,0xFE,0x10,0x40,
	0x10,0x60,0x10,0x80,0x1C,0x88,0x31,0x04,0xC2,0x7E,0x07,0xC6,0x02,0x04,0x00,0x00,




};

#endif
