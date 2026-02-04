using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using NoiseSerde;
using NoiseBackend;

namespace NoiseBackendExample;

public class Backend
{
    private readonly NoiseBackend.Backend _impl;

    public Backend(string zoPath, string modName, string procName)
    {
        _impl = new NoiseBackend.Backend(zoPath, modName, procName);
    }

    public Task<List<Comment>> GetComments(ulong id)
    {
        return _impl.Send(
            (IOutputPort outp) =>
            {
                ((ulong)0x0000).WriteUVarint(outp); // Request ID 0
                id.WriteUVarint(outp);
            },
            (IInputPort inp) =>
            {
                // Read Logic for [Comment]
                ulong count = inp.ReadUVarint();
                var list = new List<Comment>((int)count);
                for (ulong i = 0; i < count; i++)
                {
                    list.Add(Comment.Read(inp));
                }
                return list;
            }
        );
    }

    public Task<List<Story>> GetTopStories()
    {
        return _impl.Send(
            (IOutputPort outp) =>
            {
                ((ulong)0x0001).WriteUVarint(outp); // Request ID 1
            },
            (IInputPort inp) =>
            {
                // Read Logic for [Story]
                ulong count = inp.ReadUVarint();
                var list = new List<Story>((int)count);
                for (ulong i = 0; i < count; i++)
                {
                    list.Add(Story.Read(inp));
                }
                return list;
            }
        );
    }

    public Task InstallCallback(ulong id, long addr) // addr is Varint in Swift example "andAddr addr: Varint"
    {
        // Swift uses Varint for address? "andAddr addr: Varint" -> addr.write(to: out)
        // Checking Swift definition usage: installCallback(internalWithId id: UVarint, andAddr addr: Varint)
        
        return _impl.Send(
            (IOutputPort outp) =>
            {
                ((ulong)0x0002).WriteUVarint(outp); // Request ID 2
                id.WriteUVarint(outp);
                addr.WriteVarint(outp);
            },
            (IInputPort inp) =>
            {
                // Returns Void
                return 0; // Dummy return
            }
        );
    }
}
