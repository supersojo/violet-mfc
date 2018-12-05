#ifndef IGRAPHFILELISTENER_H
#define IGRAPHFILELISTENER_H

namespace violet {
    class IGraphFileListener {
        public:
            virtual void OnFileModified() = 0;
            virtual void void OnFileSaved() = 0;
    };
}

#endif
