#include <iostream>

#include <candy/base/Log.hpp>
#include <candy/utils/FileUtils.hpp>
int main()
{
  Candy::Log::Init();
  
  CANDY_CORE_INFO("Hello world from candy engine");
  
  
  std::cout << "Hello, World!" << std::endl;
  std::filesystem::path path = std::filesystem::current_path();
  Candy::Utils::FileDialog dialog(path);
  std::filesystem::path openedFile = dialog.OpenFile();
  
  CANDY_CORE_INFO("Opened file: {0}", openedFile.string());
  
  return 0;
}
