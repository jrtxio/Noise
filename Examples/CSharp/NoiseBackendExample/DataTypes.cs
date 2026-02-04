using System;
using System.Collections.Generic;
using System.Text;
using NoiseSerde;

namespace NoiseBackendExample;

public struct Comment
{
    public ulong Id { get; }
    public string Author { get; }
    public string Timestamp { get; }
    public string Text { get; }

    public Comment(ulong id, string author, string timestamp, string text)
    {
        Id = id;
        Author = author;
        Timestamp = timestamp;
        Text = text;
    }

    public static Comment Read(IInputPort inp)
    {
        var id = inp.ReadUVarint();
        var author = inp.ReadString();
        var timestamp = inp.ReadString();
        var text = inp.ReadString();
        return new Comment(id, author, timestamp, text);
    }

    public void Write(IOutputPort outp)
    {
        Id.WriteUVarint(outp);
        Author.WriteString(outp);
        Timestamp.WriteString(outp);
        Text.WriteString(outp);
    }
}

public struct Story
{
    public ulong Id { get; }
    public string Title { get; }
    public List<ulong> Comments { get; }

    public Story(ulong id, string title, List<ulong> comments)
    {
        Id = id;
        Title = title;
        Comments = comments;
    }

    public static Story Read(IInputPort inp)
    {
        var id = inp.ReadUVarint();
        var title = inp.ReadString();
        
        // Swift: [UVarint].read
        // We need to implement list reading logic similar to how Swift does it.
        // Usually list serialization first writes length, then items.
        // Assuming Serde has or we need to implement list reading logic.
        // Checking Swift Serde implementation for Arrays would be ideal, but standard pattern is length (UVarint) + items.
        
        ulong count = inp.ReadUVarint();
        var comments = new List<ulong>((int)count);
        for (ulong i = 0; i < count; i++)
        {
            comments.Add(inp.ReadUVarint());
        }

        return new Story(id, title, comments);
    }

    public void Write(IOutputPort outp)
    {
        Id.WriteUVarint(outp);
        Title.WriteString(outp);
        
        // Write list logic
        ((ulong)Comments.Count).WriteUVarint(outp);
        foreach (var c in Comments)
        {
            c.WriteUVarint(outp);
        }
    }
}
