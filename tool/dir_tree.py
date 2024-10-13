import os

# 무시할 파일 및 디렉토리 목록
ignore_list = ["README.md", "build"]

def print_directory_tree(startpath, indent="", is_last=False):
    # 디렉토리와 파일을 나누어 먼저 디렉토리, 그 후 파일을 출력
    items = sorted(os.listdir(startpath))
    directories = [item for item in items if os.path.isdir(os.path.join(startpath, item))]
    files = [item for item in items if os.path.isfile(os.path.join(startpath, item))]

    # 무시할 파일이나 폴더는 제거
    directories = [d for d in directories if d not in ignore_list]
    files = [f for f in files if f not in ignore_list]

    total_items = len(directories) + len(files)

    for idx, directory in enumerate(directories):
        is_last_item = (idx == len(directories) - 1 and len(files) == 0)
        print(f"{indent}{'└' if is_last_item else '├'} {directory}")
        print_directory_tree(os.path.join(startpath, directory), indent + ('    ' if is_last_item else '│ '), is_last_item)

        # 마지막 디렉토리 후에 빈 줄 추가, 줄을 유지하도록 '│' 삽입
        if is_last_item:
            print(f"{indent}")
        else:
            print(f"{indent}│")

    # 파일 출력
    for idx, file in enumerate(files):
        is_last_item = (idx == len(files) - 1)
        print(f"{indent}{'└' if is_last_item else '├'} {file}")

# 프로그램 시작
if __name__ == "__main__":
    # 폴더명을 입력받음 (기본 경로는 ../)
    folder_name = input("탐색할 폴더명을 입력하세요 (기본값은 ../): ") or "../"

    # 경로가 "../"인 경우, 입력 폴더명을 ../와 합침
    if folder_name != "../":
        folder_name = os.path.join("..", folder_name)

    # 유효한 경로인지 확인
    if os.path.isdir(folder_name):
        print(f"\n'{folder_name}'의 디렉토리 구조:\n")
        print_directory_tree(folder_name)
    else:
        print(f"'{folder_name}'는 유효한 폴더가 아닙니다.")
