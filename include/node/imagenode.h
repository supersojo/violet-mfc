#ifndef IMAGENODE_H
#define IMAGENODE_H
#include "../abstract/abstractnode.h"
#include "../graph/vpath.h"
#include "../graph/vimage.h"
namespace violet {
    /*
    imagenode does't use content layer
    so must rewrite draw 
    it adds VShape for additional usage
    +---+
    +---+ image
    |txt|
    +---+
    */
    class ImageNode : public AbstractNode {
        public:
            ImageNode() {
                m_image = nullptr;
                m_text = new VLineText;
            }
            void SetImage(VImage& image) {
                if (m_image)
                    delete m_image;
                m_image = &image;
            }
            VImage& GetImage() {
                return *m_image;
            }
            virtual VRect GetBounds() {
                VRect b = m_text->GetBounds();
                VPoint currentLocation = GetLocation();
                double x = currentLocation.GetX();
                double y = currentLocation.GetY();
                //double w = 
            }
            // caller must free it
            virtual VShape& GetShape() {
                return *(new VPath);
            }
            ~ImageNode() {
                if (m_image)
                    delete m_image;
                if (m_text)
                    delete m_text;
            }
        private:
            VImage* m_image;
            VLineText* m_text;
    };
}

#endif

