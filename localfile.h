#ifndef LOCALFILE_H
#define LOCALFILE_H
#include "config.h"
#include "vfile.h"
namespace violet {
    class LocalFile : public VFile {
        public:
            LocalFile(CFile& file) {
                CString& filePath = file.GetFilePath();
                Init( std::string(filePath.GetBuffer(filePath.GetLength())) );
            }
            std::string GetFileName() {
                return m_fileName;
            }
            std::string GetDirectory() {
                return m_directory;
            }
            ~LocalFile() {
            }
        private:
            void Init(std::string& fullPath) {
                CFile file;
                CFileException e;
                if (!file.Open(fullPath.c_str(),CFile::modeRead,&e)) {
                    m_fileName="";
                    m_directory="";
                    return;
                }
                CString fileName = file.GetFileName();
                m_fileName = std::string(fileName.GetBuffer(fileName.GetLength()));
                /* c:/file.txt
                      ^                
                */
                std::size_t pos = fullPath.find(m_fileName.c_str());
                m_directory = fullPath.substr(0,pos-2);//?? overflow
            }   
            std::string m_fileName;
            std::string m_directory;
    };
}


#endif
