import os
import sys

def generate_include_file(directory, output_file, exclude_files):
    # 기존 output.h 파일을 덮어쓰도록 'w' 모드로 엽니다.
    with open(output_file, 'w') as outfile:
        # 폴더 내의 모든 파일을 검색
        for filename in os.listdir(directory):
            # 파일이 .h 확장자를 가지고 있는지 확인
            if filename.endswith('.h') and filename not in exclude_files:
                # #include 문을 작성하여 파일에 추가
                outfile.write(f'#include "{filename}"\n')

if __name__ == "__main__":
    # 폴더 경로와 출력 파일 이름을 설정
    target_directory = './'  # 여기에 파일을 읽을 폴더 경로를 입력하세요
    if len(sys.argv) > 1:
        target_directory = sys.argv[1]

    output_header_file = target_directory + 'UserBehaviours.h'

    # 제외할 .h 파일 목록을 설정
    exclude_files = [
        'ExampleBehaviour.h',
        'UserBehaviours.h',
    ]

    # 파일 포함을 생성하는 함수 호출
    generate_include_file(target_directory, output_header_file, exclude_files)
    print(f'Include statements have been written to {output_header_file}.')
