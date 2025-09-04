namespace problem4
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string? InitialUrl = Console.ReadLine();

            if(InitialUrl != null)
            {
                var bfs = new BfsManager(InitialUrl);
                WikiPageNode? result = null;

                while (bfs.CurrentStep < Globals.MaxDepth && result == null)
                    result = bfs.Step();

                if(result!=null)
                {
                    List<string> rs = result.RestorePath();

                    for (int i = rs.Count - 1; i >= 0; i--)
                        Console.WriteLine(rs[i]);

                    Console.ReadLine();
                    return;
                }
            }

            Console.WriteLine("Hitler not found");
            Console.ReadLine();
            return;
        }
    }
}