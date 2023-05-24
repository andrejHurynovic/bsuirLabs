using System.Collections;
using System.IO;

namespace Shared
{
    public class FileManager : IEnumerable<KeyValuePair<string, FileInfo>>
    {
        private readonly Dictionary<string, FileInfo> _files;
        private readonly string _path;

        public int FilesCount => _files.Count;

        public FileManager(string path)
        {
            _path = path;
            var files = _files = new();
            if(!Directory.Exists(_path))
                Directory.CreateDirectory(_path);

            var dir = new DirectoryInfo(_path);
            var allFiles = dir.GetFiles();

            foreach (var f in allFiles)
            {
                files.Add(f.Name, f);
            }
        }

        public string[] GetFiles()
        {
            List<string> results = new();
            _files.Clear();
            if (!Directory.Exists(_path))
                Directory.CreateDirectory(_path);

            var dir = new DirectoryInfo(_path);
            var allFiles = dir.GetFiles();

            foreach (var f in allFiles)
            {
                _files.Add(f.Name, f);
                results.Add(f.Name);
            }

            return results.ToArray();
        }

        public bool Contains(string fileName)
        {
            return _files.ContainsKey(fileName);
        }

        public bool TryGetFile(string fileName, out FileInfo? finfo)
        {
            return _files.TryGetValue(fileName, out finfo);
        }

        public IEnumerator<KeyValuePair<string, FileInfo>> GetEnumerator()
        {
            return ((IEnumerable<KeyValuePair<string, FileInfo>>)_files).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)_files).GetEnumerator();
        }
    }
}