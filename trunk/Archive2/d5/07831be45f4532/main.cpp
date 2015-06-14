
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <thread>
#include <chrono>

using namespace std;

struct CCameraInfo
{
    string Username, Password, Address;
	int CameraID = 0;
};
 
struct CCamera
{
	CCamera(CCameraInfo Info) :
		m_Info(Info)
	{
 
	}
 
	void Reconnect(CCameraInfo Info)
	{
 
	}
 
	vector<string> GetImageURIs()
	{
		return {};
	}
private:
	CCameraInfo m_Info;
};
 
typedef std::unique_ptr<CCamera> PCamera;
 
vector<CCameraInfo> LoadNewInfos()
{
	return{};
}
 
template <typename TContainer, typename TRange, typename FOnInsert, typename FOnUpdate, typename FOnDelete>
void SortedTransform(TContainer& Container, TRange&& NewRange, FOnInsert OnInsert, FOnUpdate OnUpdate, FOnDelete OnDelete)
{
 
}
 
int main(int argc, char* argv[])
{
 
	
	map<int, PCamera> Cameras;
	
//	for (;;)
	{
		vector<CCameraInfo> NewInfos = LoadNewInfos();
		SortedTransform(Cameras, NewInfos, 
			[](auto&& Info) { return make_unique<CCamera>(std::forward<CCameraInfo>(Info)); },  // insert 
			[](auto& Camera, auto&& Info) { if (Camera->GetInfo() != Info) Camera->Reconnect(Info); },  // update
			[](auto& Camera) { return true; }   // delete - return true, do not delete - return false;, you can also update the item in the container in this method
		);
	//	this_thread::sleep_for(std::chrono::seconds(3));
	}
    
    cout << "X" << endl;

}