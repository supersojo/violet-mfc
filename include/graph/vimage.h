#ifndef VIMAGE_H
#define VIMAGE_H

namespace violet {
    class VImage {
        public:
            VImage() {
                m_width = 0;
                m_height = 0;
            }
            int GetWidth() {
                return m_width;
            }
            int GetHeight() {
                return m_height;
            }
            /* process image : scale or do something */
            VImage& GetScaledImage(int w,int h,int scaleType) {
                VImage *newImage = new VImage;
                return *newImage;
            }
            const static int SCALE_DEFAULT = 1;
            const static int SCALE_FAST    = 2;
        private:
            int m_width;
            int m_height;
    };
}

#endif
