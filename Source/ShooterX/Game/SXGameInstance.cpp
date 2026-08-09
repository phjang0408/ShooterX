// SXGameInstance.cpp

#include "SXGameInstance.h"
#include "Example/SXFlyable.h"
#include "Example/SXEagle.h"
#include "Example/SXPigeon.h"

USXGameInstance::USXGameInstance()
{	
}

void USXGameInstance::Init()
{
	Super::Init();

	USXPigeon* Pigeon76 = NewObject<USXPigeon>();
	Pigeon76->SetPigeonName(TEXT("Pigeon76"));
	Pigeon76->SetPigeonID(76);
	UE_LOG(LogTemp, Log, TEXT("[Pigeon76] Name : %s, ID : %d"), *Pigeon76->GetPigeonName(), Pigeon76->GetPigeonID());

	// 2. 파일형태로 직렬화-역직렬화 [패턴]
	// 2.1 파일 형태이므로, 경로와 파일 이름이 필요함
	// FPlatformMisc::ProjectDir(): 현재 프로젝트의 최상위 디렉토리 경로를 반환하는 역할
	// FPaths::Combine: 여러 경로 문자열을 합쳐주는 역할
	const FString SavedDirectoryPath 
		= FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));	// Combine으로 프로젝트 폴더 안에있는 Saved폴더까지 깊숙히
	UE_LOG(LogTemp, Log, TEXT("SavedDirectoryPath : %s"), *SavedDirectoryPath);
	const FString SavedFileName(TEXT("SerializedPigeon76Data.bin"));	// 파일 명에는 확장자까지 작성

	// 2.2 상대경로 지정
	// FPath:;Combine으로 FString타입의 '상대경로'를 만들 수 있음.
	FString AbsoluteFilePath
		= FPaths::Combine(*SavedDirectoryPath, *SavedFileName);
	UE_LOG(LogTemp, Log, TEXT("RelativeFilePath : %s"), *AbsoluteFilePath);

	// 2.3 절대경로 지정
	// FPaths::MakeStandardFilename(상대_경로)로 '상대 경로'를 '절대 경로'로 만들 수 있음.
	// 특히 경로 슬래시(\나 /)를 언리얼 포맷으로 깔끔하게 만들어 줌.
	FPaths::MakeStandardFilename(AbsoluteFilePath);
	UE_LOG(LogTemp, Log, TEXT("AbsoluteFilePath : %s"), *AbsoluteFilePath);


	// 3. 직렬화(파일 쓰기)
	// 구조체 --> FArchive객체
	// IFileManager::Get() : 파일 입출력 객체 접근
	// CreateFileWriter(경로) : 경로에 접근 가능한 Writer 객체 생성
	FSXPigeonData SerializedPigeon76Data(Pigeon76->GetPigeonName(), Pigeon76->GetPigeonID());
	FArchive* WriterArchive = IFileManager::Get().CreateFileWriter(*AbsoluteFilePath);
	if (WriterArchive != nullptr)
	{
		// FArchive가 Writer이므로, <<연산자는 파일에 '기록'으로 작동
		*WriterArchive << SerializedPigeon76Data;
		WriterArchive->Close();		// 다 썼으니 파일 핸들 닫기
		delete WriterArchive;		// 메모리 해제
		WriterArchive = nullptr;
	}

	// 4. 역직렬화(파일 읽기)
	// FArchive객체 --> 구조체
	// 마찬가지, 다른건 Writer대신 Reader
	FSXPigeonData DeserializedPigeon76Data;
	FArchive* ReaderArchive = IFileManager::Get().CreateFileReader(*AbsoluteFilePath);
	if (ReaderArchive != nullptr)
	{
		// FArchive가 Reader이므로, <<연산자는 파일을 '조회' 및 이를 읽어 데이터를 채울 수 있음.
		*ReaderArchive << DeserializedPigeon76Data;
		ReaderArchive->Close();		// 다 읽었으니 파일 핸들 닫기
		delete ReaderArchive;		// 메모리 해제
		ReaderArchive = nullptr;
	}

	// 5. 역직렬화를 바탕으로 새로운 객체 생성
	// 역직렬화를 통해 구조체에 
	USXPigeon* ClonedPigeon76 = NewObject<USXPigeon>();
	ClonedPigeon76->SetPigeonName(DeserializedPigeon76Data.Name);
	ClonedPigeon76->SetPigeonID(DeserializedPigeon76Data.ID);
	UE_LOG(LogTemp, Log, TEXT("[ClonsedPigeon76] Name : %s, ID : %d")
		, *ClonedPigeon76->GetPigeonName(), ClonedPigeon76->GetPigeonID());
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
