import threading
import requests

class Download:
    def download(self, url, callback_world_count):
        print(f"开始下载 {url}")
        response = requests.get(url)
        response.encoding = 'utf-8'
        callback_world_count(url, response.text)  # 回调传入 url 和文本内容

    def start_download(self, url, callback_world_count):
        thread = threading.Thread(
            target=self.download,
            args=(url, callback_world_count)
        )
        thread.start()

def world_count(url, result):
    print(f"{url} -> 字数: {len(result)}, 前5字: {result[:5]}")

def main():
    download = Download()
    url = "http://www.guyuehome.com"
    
    # 单次同步下载
    download.download(url, world_count)

    # 多线程异步下载
    for _ in range(3):
        download.start_download(url, world_count)

if __name__ == "__main__":
    main()