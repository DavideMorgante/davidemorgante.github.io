import requests
import random
import string

def fetch_arxiv_papers(author_id):
    url = f'https://arxiv.org/a/{author_id}.json'
    response = requests.get(url)
    if response.status_code == 200:
        json_data = response.json()
        if 'entries' in json_data:
            return json_data['entries']
        else:
            print("Key 'entries' not found in JSON response")
            return []
    else:
        print(f"Failed to fetch data from {url}")
        return []

def generate_random_string(length=8):
    return ''.join(random.choices(string.digits, k=length))

def consolidate_papers(author_id):
    papers = fetch_arxiv_papers(author_id)
    consolidated_papers = []

    for idx, paper in enumerate(papers, start=1):
        random_string = generate_random_string()
        consolidated_paper = {
            'random_string': random_string,
            'title': paper.get('title', 'N/A'),
            'type': 'Paper',
            'doi': paper.get('doi', 'N/A'),
            'year': int(paper['published'][:4]) if 'published' in paper else 'N/A',
            'authors': [author.strip() for author in paper.get('authors', '').split(',')],
            'abstract': paper.get('summary', 'N/A'),
            'links': [{'name': format_name(format_type), 'link': format_link(format_type, paper['formats'])} for format_type in ['pdf', 'html']]
        }
        consolidated_papers.append(consolidated_paper)

    return consolidated_papers

def format_name(format_type):
    if format_type == 'pdf':
        return 'PDF'
    elif format_type == 'html':
        return 'HTML'
    else:
        return 'Unknown'

def format_link(format_type, formats):
    return formats.get(format_type, 'N/A')

def generate_yaml(papers):
    yaml_content = ''
    for paper in papers:
        yaml_content += f"{paper['random_string']}:\n"
        yaml_content += f"  title: \"{paper['title']}\"\n"
        yaml_content += f"  type: {paper['type']}\n"
        yaml_content += f"  doi: {paper['doi']}\n"
        yaml_content += f"  year: {paper['year']}\n"
        yaml_content += "  authors:\n"
        for author in paper['authors']:
            yaml_content += f"    - {author}\n"
        yaml_content += f"  abstract: >\n    {paper['abstract']}\n"
        yaml_content += "  links:\n"
        for link in paper['links']:
            yaml_content += f"    - name: {link['name']}\n"
            yaml_content += f"      link: {link['link']}\n"
    return yaml_content

def main(author_id):
    papers = consolidate_papers(author_id)
    yaml_content = generate_yaml(papers)
    with open('_data/bibere/papers.yml', 'w') as f:
        f.write(yaml_content)

if __name__ == "__main__":
    main('0000-0002-9916-8297')
