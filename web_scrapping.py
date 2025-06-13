import requests
from bs4 import BeautifulSoup

def scrape_text_from_url(url, output_file):
    try:
        response = requests.get(url)
        response.raise_for_status()
    except Exception as e:
        print(f"Error fetching URL: {e}")
        return

    soup = BeautifulSoup(response.text, "html.parser")

    for script_or_style in soup(["script", "style"]):
        script_or_style.decompose()

    text = soup.get_text(separator='\n')
    lines = [line.strip() for line in text.splitlines()]
    text = '\n'.join(line for line in lines if line)

    with open(output_file, "w", encoding="utf-8") as f:
        f.write(text)
    print(f"Text content saved to {output_file}")

if __name__ == "__main__":
    url = input("Enter the URL to scrape: ")
    scrape_text_from_url(url, "scraped_text.txt")