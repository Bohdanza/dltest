using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace problem4
{
    public class BfsManager
    {
        public int CurrentStep { get; protected set; }
        protected HashSet<string> usedLinks;
        protected List<WikiPageNode> currentNodes;

        public BfsManager(string initialUrl) 
        {
            CurrentStep = 0;
            usedLinks = new HashSet<string>();
            currentNodes = new List<WikiPageNode>();

            currentNodes.Add(new WikiPageNode(initialUrl, null));
            usedLinks.Add(initialUrl);
        }

        public WikiPageNode? Step()
        {
            CurrentStep++;
            List<WikiPageNode> newNodes=new List<WikiPageNode>();

            if (CurrentStep == 1 && currentNodes[0].Type==2)
                return currentNodes[0];

            if (CurrentStep == 1 && currentNodes[0].Type == 0)
                return null;

            foreach (var node in currentNodes)
            {
                if (node.TryParsing(usedLinks))
                {
                    foreach (var link in node.Links)
                    {
                        WikiPageNode wpn = new WikiPageNode(link, node);

                        if (wpn.Type == 2)
                            return wpn;

                        if (wpn.Type == 1)
                        {
                            usedLinks.Add(link);
                            newNodes.Add(wpn);
                        }
                    }
                }
            }

            currentNodes = newNodes;

            return null;
        }
    }
}
