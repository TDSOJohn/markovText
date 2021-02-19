import feedparser

python_wiki_rss_url = "http://xml2.corriereobjects.it/rss/homepage.xml"

feed = feedparser.parse( python_wiki_rss_url )

print(feed)
