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
            desc = 'IGN��Դ��λ״̬&#10;0��OFF&#10;1��ACC&#10;2��ON&#10;3��CRANK&#10;4��RUN,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
