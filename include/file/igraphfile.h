#ifndef IGRAPHFILE_H
#define IGRAPHFILE_H

namespace violet {
    namespace abstract {
        class IGraph;
    }
    class IGraphFileListener;
    class IGraphFile : public VFile {
        public:
            virtual abstract::IGraph& GetGraph() = 0;
            virtual void SetSaveRequired() = 0;
            virtual bool IsSaveRequired() = 0;
            virtual void Save() = 0;
            virtual void SaveToNewLocation() = 0;
            virtual void AddListener(IGraphFileListener& listener) = 0;
            virtual void RemoveListener(IGraphFileListener& listener) = 0;
            virtual void ExportImage(/*OutputStream out, */std::string format) = 0;
            //...
    };
}

#endif
