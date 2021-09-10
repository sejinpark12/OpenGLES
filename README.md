# OpenGL ES

OpenGL ES를 이용해서 3D 모델을 렌더링 하는 방법, 물체를 바라보는 시점을 동적으로 변환하는 방법, 쉐이딩이나 조명, 텍스처 효과를 사용하는 방법 등과 같은 기본적인 컴퓨터 그래픽스 관련 테크닉을
설명합니다.

## 전제조건

프로젝트를 빌드하고 실행시키기 위해선 아래 프로그램들이 반드시 설치되어 있어야 합니다.

+ [Git](https://git-scm.com/downloads)
+ [CMake](https://cmake.org/download)
+ [Vcpkg](https://github.com/microsoft/vcpkg)

## 빌드

프로젝트에서 아래 라이브러리들을 사용하며 Vcpkg를 이용해서 라이브러리들을 설치합니다.

+ [spdlog](https://github.com/gabime/spdlog)
+ [glm](https://github.com/g-truc/glm)
+ [sdl2](https://github.com/libsdl-org/SDL)
+ [catch2](https://github.com/catchorg/Catch2)

```
vcpkg install spdlog glm sdl2 catch2
```

프로젝트는 CMake를 이용해서 생성합니다.

```
cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build [build directory]
```

## 목차

### 1. 오리엔테이션

+ [동영상](https://youtu.be/5ltQAmyo6Mo)
+ [슬라이드](https://docs.google.com/presentation/d/18XgdDWOH9SFFyHMuTS2kuhDO379Wo0qtpKugqk8h9jw/edit?usp=sharing)

### 2. 컴퓨터 그래픽스

+ [동영상](https://youtu.be/aq7UXbus7NY)
+ [슬라이드](https://docs.google.com/presentation/d/1-bCNUH0e6j4QF70cVQGsblL6h6T5sOLJ5by-h3unJxE/edit?usp=sharing)

### 3. 프로젝트 셋업

+ [동영상](https://youtu.be/zLjvoZEYcew)
+ [슬라이드](https://docs.google.com/presentation/d/1r0VwI4tPbyFKDmpEj_NDT8QYkK9F9qFtRODPaod7RIg/edit?usp=sharing)

### 4. EGL 초기화 및 종료

+ [동영상](https://youtu.be/mMIePH5AInI)
+ [슬라이드](https://docs.google.com/presentation/d/1_wH_11cCXuj_5nGiB_4HMLoXQYgn2OCe7qx9IcIdHsc/edit?usp=sharing)
+ [코드](https://github.com/GraphicsKorea/OpenGLES/tree/main/04.InitializeAndTerminateEGL)