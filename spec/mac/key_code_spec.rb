require File.expand_path(File.dirname(__FILE__) + '/../spec_helper')

include Mac

# TODO: support key lauouts other than QWERTY

describe KeyCode do
  describe '.new' do
    subject do
      KeyCode.new(key_code)
    end

    context 'key code for space key' do
      let(:key_code) do
        49
      end

      it do
        should be_printable
      end

      it do
        subject.to_s.should eql(' ')
      end
    end

    context 'key code for tab key' do
      let(:key_code) do
        48
      end

      it do
        should be_printable
      end

      it do
        subject.to_s.should eql("\t")
      end
    end

    context 'key code for "j"' do
      let(:key_code) do
        38
      end

      it do
        should be_printable
      end

      it do
        subject.to_s.should eql('j')
      end
    end

    context 'key code for return key' do
      let(:key_code) do
        36
      end

      it do
        should be_printable
      end

      it do
        subject.to_s.should eql("\r")
      end
    end

    context 'key code for non-printable key' do
      let(:key_code) do
        96
      end

      it do
        should_not be_printable
      end
    end
  end
end
