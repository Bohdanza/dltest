using System;
using System.Net;
using System.Net.Http;
using HtmlAgilityPack;

namespace problem4
{
    public class WikiPageNode
    {
        public WikiPageNode? Parent { get; protected set; }
        public List<string> Links { get; protected set; }
        public Uri URL { get; protected set; }

        //0 - Non-wiki page or invalid for other reasons
        //1 - Wiki page
        //2 - Hitler page
        public byte Type { get; protected set; }

        public WikiPageNode(string url, WikiPageNode? parent)
        {
            Parent = parent;
            Links = new List<string>();

            if (!Uri.TryCreate(url, UriKind.Absolute, out Uri uri))
            {
                Type = 0;
                return;
            }

            URL = uri;

            bool isWikipediaArticle =
                (URL.Scheme == Uri.UriSchemeHttp || URL.Scheme == Uri.UriSchemeHttps) &&
                URL.Host.EndsWith("wikipedia.org") &&
                URL.AbsolutePath.StartsWith("/wiki/");

            if (!isWikipediaArticle)
                Type = 0;
            else if (URL.AbsolutePath == Globals.HitlerPage)
                Type = 2;
            else
                Type = 1;

            return;
        }

        public bool TryParsing(HashSet<string> usedLinks)
        {
            try
            {
                HtmlWeb hwd = new HtmlWeb();
                HtmlDocument hdc = hwd.Load(URL);

                var lnk = hdc.DocumentNode.SelectNodes("//a[@href]");

                if (lnk != null)
                {
                    foreach (HtmlNode link in lnk)
                    {
                        string cst = "https://en.wikipedia.org" + link.GetAttributeValue("href", string.Empty);

                        if (!usedLinks.Contains(cst))
                            Links.Add(cst);
                    }
                }
            }
            catch (Exception ex)
            {
                return false;
            }

            return true;
        }
    
        public List<string> RestorePath()
        {
            List<string> res = new List<string>();
            var currentParent = this;

            while(currentParent!=null)
            {
                res.Add(currentParent.URL.OriginalString);
                currentParent = currentParent.Parent;
            }

            return res;
        }
    }
}