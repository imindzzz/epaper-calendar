#include "header.h"

// alternately you can copy the constructor from GxEPD2_display_selection.h of GxEPD_Example to here
// and adapt it to the ESP32 Driver wiring, e.g.
//GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25)); // GDEH0154D67

// comment out unused bitmaps to reduce code space used
// #include "bitmaps/Bitmaps200x200.h" // 1.54" b/w
// #include "bitmaps/Bitmaps104x212.h" // 2.13" b/w flexible GDEW0213I5F
// #include "bitmaps/Bitmaps128x250.h" // 2.13" b/w
// #include "bitmaps/Bitmaps128x296.h" // 2.9"  b/w
// #include "bitmaps/Bitmaps176x264.h" // 2.7"  b/w
#include "bitmaps/Bitmaps400x300.h" // 4.2"  b/w
// #include "bitmaps/Bitmaps640x384.h" // 7.5"  b/w
// 3-color
// #include "bitmaps/Bitmaps3c200x200.h" // 1.54" b/w/r
// #include "bitmaps/Bitmaps3c104x212.h" // 2.13" b/w/r
// #include "bitmaps/Bitmaps3c128x296.h" // 2.9"  b/w/r
// #include "bitmaps/Bitmaps3c176x264.h" // 2.7"  b/w/r
// #include "bitmaps/Bitmaps3c400x300.h" // 4.2"  b/w/r

// note for partial update window and setPartialWindow() method:
// partial update window size and position is on byte boundary in physical x direction
// the size is increased in setPartialWindow() if x or w are not multiple of 8 for even rotation, y or h for odd rotation
// see also comment in GxEPD2_BW.h, GxEPD2_3C.h or GxEPD2_GFX.h for method setPartialWindow()

#ifdef _GxBitmaps400x300_H_
void drawBitmaps400x300()
{
#if !defined(__AVR)
    const unsigned char *bitmaps[] =
        {
            Bitmap400x300_1, Bitmap400x300_2};
#else
    const unsigned char *bitmaps[] = {}; // not enough code space
#endif
    if (display.epd2.panel == GxEPD2::GDEW042T2)
    {
        for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
            } while (display.nextPage());
            delay(2000);
        }
    }
}
#endif

#ifdef _GxBitmaps200x200_H_
void drawBitmaps200x200()
{
#if defined(__AVR)
    const unsigned char *bitmaps[] =
        {
            logo200x200, first200x200 //, second200x200, third200x200, fourth200x200, fifth200x200, sixth200x200, senventh200x200, eighth200x200
        };
#elif defined(_BOARD_GENERIC_STM32F103C_H_)
    const unsigned char *bitmaps[] =
        {
            logo200x200, first200x200, second200x200, third200x200, fourth200x200, fifth200x200 //, sixth200x200, senventh200x200, eighth200x200
        };
#else
    const unsigned char *bitmaps[] =
        {
            logo200x200, first200x200, second200x200, third200x200, fourth200x200, fifth200x200, sixth200x200, senventh200x200, eighth200x200};
#endif
    if ((display.epd2.panel == GxEPD2::GDEP015OC1) || (display.epd2.panel == GxEPD2::GDEH0154D67))
    {
        bool m = display.mirror(true);
        for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
            } while (display.nextPage());
            delay(2000);
        }
        display.mirror(m);
    }
    //else
    {
        bool mirror_y = (display.epd2.panel != GxEPD2::GDE0213B1);
        display.clearScreen(); // use default for white
        int16_t x = (int16_t(display.epd2.WIDTH) - 200) / 2;
        int16_t y = (int16_t(display.epd2.HEIGHT) - 200) / 2;
        for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
        {
            display.drawImage(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
            delay(2000);
        }
    }
    bool mirror_y = (display.epd2.panel != GxEPD2::GDE0213B1);
    for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
    {
        int16_t x = -60;
        int16_t y = -60;
        for (uint16_t j = 0; j < 10; j++)
        {
            display.writeScreenBuffer(); // use default for white
            display.writeImage(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
            display.refresh(true);
            if (display.epd2.hasFastPartialUpdate)
            {
                // for differential update: set previous buffer equal to current buffer in controller
                display.epd2.writeScreenBufferAgain(); // use default for white
                display.epd2.writeImageAgain(bitmaps[i], x, y, 200, 200, false, mirror_y, true);
            }
            delay(2000);
            x += 40;
            y += 40;
            if ((x >= int16_t(display.epd2.WIDTH)) || (y >= int16_t(display.epd2.HEIGHT)))
                break;
        }
        if (!display.epd2.hasFastPartialUpdate)
            break; // comment out for full show
        break;     // comment out for full show
    }
    display.writeScreenBuffer(); // use default for white
    display.writeImage(bitmaps[0], int16_t(0), 0, 200, 200, false, mirror_y, true);
    display.writeImage(bitmaps[0], int16_t(int16_t(display.epd2.WIDTH) - 200), int16_t(display.epd2.HEIGHT) - 200, 200, 200, false, mirror_y, true);
    display.refresh(true);
    delay(2000);
}
#endif

#ifdef _GxBitmaps104x212_H_
void drawBitmaps104x212()
{
#if !defined(__AVR)
    const unsigned char *bitmaps[] =
        {
            WS_Bitmap104x212, Bitmap104x212_1, Bitmap104x212_2, Bitmap104x212_3};
#else
    const unsigned char *bitmaps[] =
        {
            WS_Bitmap104x212, Bitmap104x212_1, Bitmap104x212_2, Bitmap104x212_3};
#endif
    if (display.epd2.panel == GxEPD2::GDEW0213I5F)
    {
        for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
            } while (display.nextPage());
            delay(2000);
        }
    }
}
#endif

#ifdef _GxBitmaps128x250_H_
void drawBitmaps128x250()
{
#if !defined(__AVR)
    const unsigned char *bitmaps[] =
        {
            Bitmap128x250_1, logo128x250, first128x250, second128x250, third128x250};
#else
    const unsigned char *bitmaps[] =
        {
            Bitmap128x250_1, logo128x250, first128x250, second128x250, third128x250};
#endif
    if ((display.epd2.panel == GxEPD2::GDE0213B1) || (display.epd2.panel == GxEPD2::GDEH0213B72))
    {
        bool m = display.mirror(true);
        for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
            } while (display.nextPage());
            delay(2000);
        }
        display.mirror(m);
    }
}
#endif

#ifdef _GxBitmaps128x296_H_
void drawBitmaps128x296()
{
#if !defined(__AVR)
    const unsigned char *bitmaps[] =
        {
            Bitmap128x296_1, logo128x296, first128x296, second128x296, third128x296};
#else
    const unsigned char *bitmaps[] =
        {
            Bitmap128x296_1, logo128x296 //, first128x296, second128x296, third128x296
        };
#endif
    if (display.epd2.panel == GxEPD2::GDEH029A1)
    {
        bool m = display.mirror(true);
        for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
            } while (display.nextPage());
            delay(2000);
        }
        display.mirror(m);
    }
}
#endif

#ifdef _GxBitmaps176x264_H_
void drawBitmaps176x264()
{
#if !defined(__AVR)
    const unsigned char *bitmaps[] =
        {
            Bitmap176x264_1, Bitmap176x264_2, Bitmap176x264_3, Bitmap176x264_4, Bitmap176x264_5};
#else
    const unsigned char *bitmaps[] =
        {
            Bitmap176x264_1, Bitmap176x264_2 //, Bitmap176x264_3, Bitmap176x264_4, Bitmap176x264_5
        };
#endif
    if (display.epd2.panel == GxEPD2::GDEW027W3)
    {
        for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
            } while (display.nextPage());
            delay(2000);
        }
    }
}
#endif

#ifdef _GxBitmaps640x384_H_
void drawBitmaps640x384()
{
#if !defined(__AVR)
    const unsigned char *bitmaps[] =
        {
            Bitmap640x384_1, Bitmap640x384_2};
#else
    const unsigned char *bitmaps[] = {}; // not enough code space
#endif
    if ((display.epd2.panel == GxEPD2::GDEW075T8) || (display.epd2.panel == GxEPD2::GDEW075Z09))
    {
        for (uint16_t i = 0; i < sizeof(bitmaps) / sizeof(char *); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmaps[i], display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
            } while (display.nextPage());
            delay(2000);
        }
    }
}
#endif

#ifdef _WS_Bitmaps800x600_H_
void drawBitmaps800x600()
{
#if defined(ESP8266) || defined(ESP32)
    if (display.epd2.panel == GxEPD2::ED060SCT)
    {
        //    Serial.print("sizeof(WS_zoo_800x600) is "); Serial.println(sizeof(WS_zoo_800x600));
        display.drawNative(WS_zoo_800x600, 0, 0, 0, 800, 600, false, false, true);
        delay(2000);
        //    Serial.print("sizeof(WS_pic_1200x825) is "); Serial.println(sizeof(WS_pic_1200x825));
        //    display.drawNative((const uint8_t*)WS_pic_1200x825, 0, 0, 0, 1200, 825, false, false, true);
        //    delay(2000);
        //    Serial.print("sizeof(WS_acaa_1024x731) is "); Serial.println(sizeof(WS_acaa_1024x731));
        //    display.drawNative(WS_acaa_1024x731, 0, 0, 0, 1024, 731, false, false, true);
        //    delay(2000);
    }
#endif
}
#endif

struct bitmap_pair
{
    const unsigned char *black;
    const unsigned char *red;
};

#ifdef _GxBitmaps3c200x200_H_
void drawBitmaps3c200x200()
{
    bitmap_pair bitmap_pairs[] =
        {
            //{Bitmap3c200x200_black, Bitmap3c200x200_red},
            {WS_Bitmap3c200x200_black, WS_Bitmap3c200x200_red}};
    if (display.epd2.panel == GxEPD2::GDEW0154Z04)
    {
        display.firstPage();
        do
        {
            display.fillScreen(GxEPD_WHITE);
            // Bitmap3c200x200_black has 2 bits per pixel
            // taken from Adafruit_GFX.cpp, modified
            int16_t byteWidth = (display.epd2.WIDTH + 7) / 8; // Bitmap scanline pad = whole byte
            uint8_t byte = 0;
            for (int16_t j = 0; j < display.epd2.HEIGHT; j++)
            {
                for (int16_t i = 0; i < display.epd2.WIDTH; i++)
                {
                    if (i & 3)
                        byte <<= 2;
                    else
                    {
#if defined(__AVR) || defined(ESP8266) || defined(ESP32)
                        byte = pgm_read_byte(&Bitmap3c200x200_black[j * byteWidth * 2 + i / 4]);
#else
                        byte = Bitmap3c200x200_black[j * byteWidth * 2 + i / 4];
#endif
                    }
                    if (!(byte & 0x80))
                    {
                        display.drawPixel(i, j, GxEPD_BLACK);
                    }
                }
            }
            display.drawInvertedBitmap(0, 0, Bitmap3c200x200_red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
        } while (display.nextPage());
        delay(2000);
        for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
                display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
            } while (display.nextPage());
            delay(2000);
        }
    }
    if (display.epd2.hasColor)
    {
        display.clearScreen(); // use default for white
        int16_t x = (int16_t(display.epd2.WIDTH) - 200) / 2;
        int16_t y = (int16_t(display.epd2.HEIGHT) - 200) / 2;
        for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
        {
            display.drawImage(bitmap_pairs[i].black, bitmap_pairs[i].red, x, y, 200, 200, false, false, true);
            delay(2000);
        }
        for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
        {
            int16_t x = -60;
            int16_t y = -60;
            for (uint16_t j = 0; j < 10; j++)
            {
                display.writeScreenBuffer(); // use default for white
                display.writeImage(bitmap_pairs[i].black, bitmap_pairs[i].red, x, y, 200, 200, false, false, true);
                display.refresh();
                delay(1000);
                x += 40;
                y += 40;
                if ((x >= int16_t(display.epd2.WIDTH)) || (y >= int16_t(display.epd2.HEIGHT)))
                    break;
            }
        }
        display.writeScreenBuffer(); // use default for white
        display.writeImage(bitmap_pairs[0].black, bitmap_pairs[0].red, 0, 0, 200, 200, false, false, true);
        display.writeImage(bitmap_pairs[0].black, bitmap_pairs[0].red, int16_t(display.epd2.WIDTH) - 200, int16_t(display.epd2.HEIGHT) - 200, 200, 200, false, false, true);
        display.refresh();
        delay(2000);
    }
}
#endif

#ifdef _GxBitmaps3c104x212_H_
void drawBitmaps3c104x212()
{
#if !defined(__AVR)
    bitmap_pair bitmap_pairs[] =
        {
            {Bitmap3c104x212_1_black, Bitmap3c104x212_1_red},
            {Bitmap3c104x212_2_black, Bitmap3c104x212_2_red},
            {WS_Bitmap3c104x212_black, WS_Bitmap3c104x212_red}};
#else
    bitmap_pair bitmap_pairs[] =
        {
            {Bitmap3c104x212_1_black, Bitmap3c104x212_1_red},
            //{Bitmap3c104x212_2_black, Bitmap3c104x212_2_red},
            {WS_Bitmap3c104x212_black, WS_Bitmap3c104x212_red}};
#endif
    if (display.epd2.panel == GxEPD2::GDEW0213Z16)
    {
        for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
                if (bitmap_pairs[i].red == WS_Bitmap3c104x212_red)
                {
                    display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
                }
                else
                    display.drawBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
            } while (display.nextPage());
            delay(2000);
        }
    }
}
#endif

#ifdef _GxBitmaps3c128x296_H_
void drawBitmaps3c128x296()
{
#if !defined(__AVR)
    bitmap_pair bitmap_pairs[] =
        {
            {Bitmap3c128x296_1_black, Bitmap3c128x296_1_red},
            {Bitmap3c128x296_2_black, Bitmap3c128x296_2_red},
            {WS_Bitmap3c128x296_black, WS_Bitmap3c128x296_red}};
#else
    bitmap_pair bitmap_pairs[] =
        {
            //{Bitmap3c128x296_1_black, Bitmap3c128x296_1_red},
            //{Bitmap3c128x296_2_black, Bitmap3c128x296_2_red},
            {WS_Bitmap3c128x296_black, WS_Bitmap3c128x296_red}};
#endif
    if (display.epd2.panel == GxEPD2::GDEW029Z10)
    {
        for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
                if (bitmap_pairs[i].red == WS_Bitmap3c128x296_red)
                {
                    display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
                }
                else
                    display.drawBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
            } while (display.nextPage());
            delay(2000);
        }
    }
}
#endif

#ifdef _GxBitmaps3c176x264_H_
void drawBitmaps3c176x264()
{
    bitmap_pair bitmap_pairs[] =
        {
            {Bitmap3c176x264_black, Bitmap3c176x264_red}};
    if (display.epd2.panel == GxEPD2::GDEW027C44)
    {
        for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
                display.drawBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
            } while (display.nextPage());
            delay(2000);
        }
    }
}
#endif

#ifdef _GxBitmaps3c400x300_H_
void drawBitmaps3c400x300()
{
#if !defined(__AVR)
    bitmap_pair bitmap_pairs[] =
        {
            {Bitmap3c400x300_1_black, Bitmap3c400x300_1_red},
            {Bitmap3c400x300_2_black, Bitmap3c400x300_2_red},
            {WS_Bitmap3c400x300_black, WS_Bitmap3c400x300_red}};
#else
    bitmap_pair bitmap_pairs[] = {}; // not enough code space
#endif
    if (display.epd2.panel == GxEPD2::GDEW042Z15)
    {
        for (uint16_t i = 0; i < sizeof(bitmap_pairs) / sizeof(bitmap_pair); i++)
        {
            display.firstPage();
            do
            {
                display.fillScreen(GxEPD_WHITE);
                display.drawInvertedBitmap(0, 0, bitmap_pairs[i].black, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
                display.drawInvertedBitmap(0, 0, bitmap_pairs[i].red, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_RED);
            } while (display.nextPage());
            delay(2000);
        }
    }
}
#endif

void drawBitmaps()
{
    display.setFullWindow();
#ifdef _GxBitmaps104x212_H_
    drawBitmaps104x212();
#endif
#ifdef _GxBitmaps128x250_H_
    drawBitmaps128x250();
#endif
#ifdef _GxBitmaps128x296_H_
    drawBitmaps128x296();
#endif
#ifdef _GxBitmaps176x264_H_
    drawBitmaps176x264();
#endif
#ifdef _GxBitmaps400x300_H_
    drawBitmaps400x300();
#endif
#ifdef _GxBitmaps640x384_H_
    drawBitmaps640x384();
#endif
#ifdef _WS_Bitmaps800x600_H_
    drawBitmaps800x600();
#endif
    // 3-color
#ifdef _GxBitmaps3c104x212_H_
    drawBitmaps3c104x212();
#endif
#ifdef _GxBitmaps3c128x296_H_
    drawBitmaps3c128x296();
#endif
#ifdef _GxBitmaps3c176x264_H_
    drawBitmaps3c176x264();
#endif
#ifdef _GxBitmaps3c400x300_H_
    drawBitmaps3c400x300();
#endif
    // show these after the specific bitmaps
#ifdef _GxBitmaps200x200_H_
    drawBitmaps200x200();
#endif
    // 3-color
#ifdef _GxBitmaps3c200x200_H_
    drawBitmaps3c200x200();
#endif
}