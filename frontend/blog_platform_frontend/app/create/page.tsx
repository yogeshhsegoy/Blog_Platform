"use client";

import React, { useState, useEffect } from "react";
import Link from "next/link";
import { Editor, EditorState, RichUtils, convertToRaw } from "draft-js";
import "draft-js/dist/Draft.css";

const CreateBlogPage = () => {
  const [blogData, setBlogData] = useState({
    title: "",
    summary: "",
    category: "",
    tags: [] as string[],
    schedule: "",
    allowComments: true,
  });

  const [editorState, setEditorState] = useState(() => EditorState.createEmpty());
  const [tagInput, setTagInput] = useState("");
  const [coverImage, setCoverImage] = useState<File | null>(null);
  const [coverPreview, setCoverPreview] = useState<string | null>(null);
  const [previewMode, setPreviewMode] = useState(false);

  // Auto-save blogData to localStorage
  useEffect(() => {
    const savedData = localStorage.getItem("draftBlogPost");
    if (savedData) {
      const parsed = JSON.parse(savedData);
      setBlogData(parsed.blogData || blogData);
      // For simplicity, we're not restoring editorState.
    }
  }, []);

  useEffect(() => {
    localStorage.setItem("draftBlogPost", JSON.stringify({ blogData }));
  }, [blogData]);

  const handleChange = (e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement | HTMLSelectElement>) => {
    const { name, value } = e.target;
    setBlogData((prev) => ({ ...prev, [name]: value }));
  };

  const handleTagAdd = (e: React.FormEvent) => {
    e.preventDefault();
    if (tagInput && !blogData.tags.includes(tagInput.trim())) {
      setBlogData((prev) => ({ ...prev, tags: [...prev.tags, tagInput.trim()] }));
      setTagInput("");
    }
  };

  const removeTag = (index: number) => {
    setBlogData((prev) => ({
      ...prev,
      tags: prev.tags.filter((_, i) => i !== index),
    }));
  };

  const handleImageChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0];
    if (file) {
      setCoverImage(file);
      const reader = new FileReader();
      reader.onloadend = () => setCoverPreview(reader.result as string);
      reader.readAsDataURL(file);
    }
  };

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    const contentState = editorState.getCurrentContent();
    const rawContent = convertToRaw(contentState);

    const postData = {
      ...blogData,
      content: rawContent,
      coverImage,
    };

    console.log("Blog post created:", postData);
    // Connect this to your backend to save the blog post

    localStorage.removeItem("draftBlogPost");
  };

  const handleKeyCommand = (command: string, editorState: EditorState) => {
    const newState = RichUtils.handleKeyCommand(editorState, command);
    if (newState) {
      setEditorState(newState);
      return "handled";
    }
    return "not-handled";
  };

  const onUnderlineClick = () => {
    setEditorState(RichUtils.toggleInlineStyle(editorState, "UNDERLINE"));
  };

  const onBoldClick = () => {
    setEditorState(RichUtils.toggleInlineStyle(editorState, "BOLD"));
  };

  const onItalicClick = () => {
    setEditorState(RichUtils.toggleInlineStyle(editorState, "ITALIC"));
  };

const onHeadingClick = (level: string) => {
  // Get the current selection
  const selection = editorState.getSelection();
  
  // Check if there's any selected text
  if (!selection.isCollapsed()) {
    setEditorState(RichUtils.toggleBlockType(editorState, level));
  } else {
    // If no text is selected, just change the block type for the current block
    const contentState = editorState.getCurrentContent();
    const blockKey = selection.getStartKey();
    const block = contentState.getBlockForKey(blockKey);
    const blockType = block.getType();
    
    // If already this heading type, revert to unstyled
    const newType = blockType === level ? 'unstyled' : level;
    
    setEditorState(RichUtils.toggleBlockType(editorState, newType));
  }
};

  const onBlockquoteClick = () => {
    setEditorState(RichUtils.toggleBlockType(editorState, "blockquote"));
  };

  return (
    <div className="min-h-screen bg-[rgb(213,208,202)] text-[rgb(21,21,21)] font-sans relative">
      {/* Denser Dot Matrix Background */}
      <div className="absolute inset-0 bg-[radial-gradient(circle,rgb(110,110,110,0.2)_1px,transparent_1px)] bg-[size:8px_8px] opacity-50"></div>

      {/* Navbar */}
      <nav className="flex justify-between items-center p-6 bg-[rgb(213,208,202)] relative z-10">
        <div className="text-2xl font-extrabold tracking-wide">blog.proj</div>
        <div className="space-x-6 text-sm font-medium">
          <a href="/" className="hover:text-[rgb(151,151,151)] transition">Home</a>
          <a href="/about" className="hover:text-[rgb(151,151,151)] transition">About</a>
          <a href="/create" className="hover:text-[rgb(151,151,151)] transition">Create Blog</a>
          <a href="/signup" className="hover:text-[rgb(151,151,151)] transition">Create Account</a>
          <a href="/signin" className="hover:text-[rgb(151,151,151)] transition">Sign In</a>
          <a href="/myprofile" className="hover:text-[rgb(151,151,151)] transition">My Profile</a>
        </div>
      </nav>

      {/* Create Blog Form */}
      <div className="p-8 w-full max-w-4xl mx-auto mt-10 relative z-10">
        <h1 className="text-3xl font-bold text-center mb-6">Create a New Blog Post</h1>
        <form onSubmit={handleSubmit} className="space-y-6">
          {/* Title */}
          <div>
            <label className="block text-sm font-medium">Title</label>
            <input
              type="text"
              name="title"
              value={blogData.title}
              onChange={handleChange}
              className="w-full p-2 border rounded-md bg-[rgb(213,208,202)] focus:outline-none focus:ring-2 focus:ring-[rgb(151,151,151)]"
              required
            />
          </div>

          {/* Summary */}
          <div>
            <label className="block text-sm font-medium">Summary</label>
            <textarea
              name="summary"
              value={blogData.summary}
              onChange={handleChange}
              className="w-full p-2 border rounded-md bg-[rgb(213,208,202)] focus:outline-none focus:ring-2 focus:ring-[rgb(151,151,151)]"
              rows={3}
              placeholder="A brief summary of your post..."
            />
          </div>

          {/* Cover Image */}
          <div>
            <label className="block text-sm font-medium">Cover Image</label>
            <input
              type="file"
              accept="image/*"
              onChange={handleImageChange}
              className="w-full p-2"
            />
            {coverPreview && (
              <img
                src={coverPreview}
                alt="Cover Preview"
                className="mt-2 h-48 object-cover rounded-md"
              />
            )}
          </div>

          {/* Category */}
          <div>
            <label className="block text-sm font-medium">Category</label>
            <select
              name="category"
              value={blogData.category}
              onChange={handleChange}
              className="w-full p-2 border rounded-md bg-[rgb(213,208,202)] focus:outline-none focus:ring-2 focus:ring-[rgb(151,151,151)]"
              required
            >
              <option value="">Select a category</option>
              <option value="tech">Tech</option>
              <option value="lifestyle">Lifestyle</option>
              <option value="travel">Travel</option>
              <option value="food">Food</option>
            </select>
          </div>

          {/* Tags */}
          <div>
            <label className="block text-sm font-medium">Tags</label>
            <div className="flex space-x-2">
              <input
                type="text"
                value={tagInput}
                onChange={(e) => setTagInput(e.target.value)}
                className="flex-1 p-2 border rounded-md bg-[rgb(213,208,202)] focus:outline-none focus:ring-2 focus:ring-[rgb(151,151,151)]"
                placeholder="Enter tag and press Add"
              />
              <button
                onClick={handleTagAdd}
                className="px-4 py-2 bg-[rgb(21,21,21)] text-white rounded-md hover:bg-[rgb(51,51,51)] transition"
              >
                Add
              </button>
            </div>
            <div className="mt-2 flex flex-wrap gap-2">
              {blogData.tags.map((tag, index) => (
                <span
                  key={index}
                  className="bg-[rgb(151,151,151)] text-white px-2 py-1 rounded-full text-xs flex items-center"
                >
                  {tag}
                  <button
                    type="button"
                    onClick={() => removeTag(index)}
                    className="ml-2 text-[rgb(213,208,202)] hover:text-white"
                  >
                    &times;
                  </button>
                </span>
              ))}
            </div>
          </div>

          {/* Content using Draft.js */}
          <div>
            <label className="block text-sm font-medium mb-2">Content</label>
            <div className="p-2 border rounded-md bg-white min-h-[200px]">
              <div className="flex space-x-2 mb-2">
                <button onClick={() => onBoldClick()} className="px-2 py-1 bg-gray-200 rounded">Bold</button>
                <button onClick={() => onItalicClick()} className="px-2 py-1 bg-gray-200 rounded">Italic</button>
                <button onClick={() => onUnderlineClick()} className="px-2 py-1 bg-gray-200 rounded">Underline</button>
                <button onClick={() => onHeadingClick('header-one')} className="px-2 py-1 bg-gray-200 rounded">H1</button>
                <button onClick={() => onHeadingClick('header-two')} className="px-2 py-1 bg-gray-200 rounded">H2</button>
                <button onClick={() => onBlockquoteClick()} className="px-2 py-1 bg-gray-200 rounded">Blockquote</button>
              </div>
              <Editor
                editorState={editorState}
                onChange={setEditorState}
                handleKeyCommand={handleKeyCommand}
                placeholder="Write your blog post content here..."
              />
            </div>
          </div>

          {/* Scheduling */}
          <div>
            <label className="block text-sm font-medium">Schedule Post (optional)</label>
            <input
              type="datetime-local"
              name="schedule"
              value={blogData.schedule}
              onChange={handleChange}
              className="w-full p-2 border rounded-md bg-[rgb(213,208,202)] focus:outline-none focus:ring-2 focus:ring-[rgb(151,151,151)]"
            />
          </div>

          {/* Comments Toggle */}
          <div className="flex items-center space-x-2">
            <input
              type="checkbox"
              name="allowComments"
              checked={blogData.allowComments}
              onChange={(e) =>
                setBlogData((prev) => ({ ...prev, allowComments: e.target.checked }))
              }
              className="h-4 w-4"
            />
            <label className="text-sm">Allow Comments</label>
          </div>

          {/* Preview Toggle & Submit */}
          <div className="flex justify-between items-center">
            <button
              type="button"
              onClick={() => setPreviewMode(!previewMode)}
              className="px-4 py-2 bg-[rgb(151,151,151)] text-white rounded-md hover:bg-[rgb(171,171,171)] transition"
            >
              {previewMode ? "Edit Mode" : "Preview Mode"}
            </button>
            <button
              type="submit"
              className="px-6 py-2 bg-[rgb(21,21,21)] text-white rounded-lg hover:bg-[rgb(51,51,51)] transition font-semibold"
            >
              Publish Blog Post
            </button>
          </div>
        </form>

        {/* Preview Section */}
        {previewMode && (
          <div className="mt-10 p-6 bg-white border rounded-md shadow-md">
            <h2 className="text-2xl font-bold mb-4">{blogData.title || "Post Title"}</h2>
            {coverPreview && (
              <img
                src={coverPreview}
                alt="Cover Preview"
                className="w-full h-64 object-cover mb-4 rounded-md"
              />
            )}
            <p className="italic mb-4">{blogData.summary || "A brief summary..."}</p>
            <div className="mb-4">
              <strong>Category:</strong> {blogData.category || "None"}
            </div>
            <div className="mb-4">
              <strong>Tags:</strong>{" "}
              {blogData.tags.length > 0 ? blogData.tags.join(", ") : "None"}
            </div>
            <div className="mb-4">
              <strong>Content Preview:</strong>
              <pre className="bg-gray-100 p-2 mt-2 overflow-auto text-xs">
                {JSON.stringify(convertToRaw(editorState.getCurrentContent()), null, 2)}
              </pre>
            </div>
            {blogData.schedule && (
              <div className="mt-4 text-sm text-gray-500">
                Scheduled for: {new Date(blogData.schedule).toLocaleString()}
              </div>
            )}
            <div className="mt-4 text-sm">
              Comments: {blogData.allowComments ? "Enabled" : "Disabled"}
            </div>
          </div>
        )}
      </div>
    </div>
  );
};

export default CreateBlogPage;
