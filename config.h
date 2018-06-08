#pragma once
const int ESC = 27;
const int dong = 2;
const int cot = 2 ;
const int Up = 72;
const int Down = 80;
const int WHITE = 15;
char menu [4][50] = {"1. Choose image to proccess                   ",
                     "2. Choose filters                             ",
                     "3. Save Image                                 ",
                     "4. Exit                                       "
                    };
char pic [6][50] = {"1. mona_lisa.ascii.pgm                        ",
                     "2. venus2.ascii.pgm                           ",
                     "3. balloons.ascii.pgm                         ",
                     "4. brain_604.ascii.pgm                        ",
                     "5. casablanca.ascii.pgm                       ",
                     "6. back                                       "
                    };
char filters [6][50] = {"1. Negative transformation                    ",
                     "2. Log transformation                         ",
                     "3. Histogram equalization                     ",
                     "4. Smoothing linear filter                    ",
                     "5. Laplacian filter                           ",
                     "6. Back to menu                               ",
                    };
