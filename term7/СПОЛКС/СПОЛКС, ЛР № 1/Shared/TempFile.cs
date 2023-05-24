using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shared
{
    public static class TempFile
    {
        private static string _tempPath = Path.Combine(Directory.GetCurrentDirectory(), "Files", "TempFile.bin");
        private static string _dataPath = Path.Combine(Directory.GetCurrentDirectory(), "Files", "DataFile.bin");

        static TempFile()
        {
            string path = Path.Combine(Directory.GetCurrentDirectory(), "Files");
            if (!Directory.Exists(path))
                Directory.CreateDirectory(path);
        }

        public static bool IsExist()
        {
            return File.Exists(_dataPath) && File.Exists(_tempPath);
        }

        public static void GetInfo(out long allChunks, out long downloadedChuks, out byte[] fileKey)
        {
            var br = new BinaryReader(File.OpenRead(_dataPath));
            allChunks = br.ReadInt64();
            downloadedChuks = br.ReadInt64();
            var keySize = br.ReadInt32();
            fileKey = br.ReadBytes(keySize);
            br.Close();
        }

        public static void Add(long downloadedChunks, byte[] data)
        {
            FileStream fstream = File.Open(_tempPath, FileMode.Append);
            fstream.Write(data);
            fstream.Close();

            GetInfo(out var allChunks, out var _, out var fileKey);
            File.Delete(_dataPath);
            var bw = new BinaryWriter(File.Create(_dataPath));
            bw.Write(allChunks);
            bw.Write(downloadedChunks);
            bw.Write(fileKey.Length);
            bw.Write(fileKey);
            bw.Close();
        }

        public static void Finish(string path)
        {
            File.Move(_tempPath, path);
            Delete();
        }

        public static void Create(long allChunks, long downloadedChunks, byte[] fileKey)
        {
            FileStream fstream = File.Create(_tempPath);
            fstream.Close();

            var bw = new BinaryWriter(File.Create(_dataPath));
            bw.Write(allChunks);
            bw.Write(downloadedChunks);
            bw.Write(fileKey.Length);
            bw.Write(fileKey);
            bw.Close();
        }

        public static void Delete()
        {
            File.Delete(_dataPath);
            if(File.Exists(_tempPath))
            {
                File.Delete(_tempPath);
            }
        }
    }
}
