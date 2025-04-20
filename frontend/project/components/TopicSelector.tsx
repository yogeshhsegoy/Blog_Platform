'use client';

import { Checkbox } from "@/components/ui/checkbox";
import { AVAILABLE_TOPICS } from "@/lib/constants";

interface TopicSelectorProps {
  selectedTopics: string[];
  onTopicChange: (topic: string, checked: boolean) => void;
}

export function TopicSelector({ selectedTopics, onTopicChange }: TopicSelectorProps) {
  return (
    <div className="grid grid-cols-2 md:grid-cols-3 gap-3 mt-3">
      {AVAILABLE_TOPICS.map((topic) => (
        <div 
          key={topic} 
          className={`flex items-center space-x-2 rounded-md border p-3 transition-colors ${
            selectedTopics.includes(topic.toLowerCase()) 
              ? 'border-primary bg-primary/5' 
              : 'border-input'
          }`}
        >
          <Checkbox 
            id={`topic-${topic}`}
            checked={selectedTopics.includes(topic.toLowerCase())}
            onCheckedChange={(checked) => onTopicChange(topic.toLowerCase(), checked as boolean)}
          />
          <label 
            htmlFor={`topic-${topic}`}
            className="text-sm font-medium leading-none cursor-pointer w-full"
          >
            {topic}
          </label>
        </div>
      ))}
    </div>
  );
}