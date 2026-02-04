using System;
using System.Collections.Generic;
using System.Text;
using NoiseSerde;

namespace NoiseBackendExample;

public class Comment
{
    public ulong Id { get; set; }
    public string Author { get; set; }
    public string Timestamp { get; set; }
    public string Text { get; set; }

    public Comment() 
    {
        Id = 0;
        Author = "";
        Timestamp = "";
        Text = "";
    }

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

public class Story
{
    public ulong Id { get; set; }
    public string Title { get; set; }
    public List<ulong> Comments { get; set; }

    public Story()
    {
        Id = 0;
        Title = "";
        Comments = new List<ulong>();
    }

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
        
        ((ulong)Comments.Count).WriteUVarint(outp);
        foreach (var c in Comments)
        {
            c.WriteUVarint(outp);
        }
    }
}
