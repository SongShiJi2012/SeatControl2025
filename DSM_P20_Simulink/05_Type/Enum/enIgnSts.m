%% Create enIgnSts enum

classdef enIgnSts < Simulink.IntEnumType

    enumeration
        eOff(0)
        eAcc(1)
        eOn(2)
        eCrank(3)
        eRun(4)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enIgnSts.eOff;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = 'IGNµçÔ´µµÎ»×´Ì¬&#10;0£ºOFF&#10;1£ºACC&#10;2£ºON&#10;3£ºCRANK&#10;4£ºRUN,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
