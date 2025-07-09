%% Create enSeatMemStsAndMsg enum

classdef enSeatMemStsAndMsg < Simulink.IntEnumType

    enumeration
        EN_INACTIVE(0)
        EN_SEAT_POSI_1_MEM_SUCCED(1)
        EN_SEAT_POSI_2_MEM_SUCCED(2)
        EN_SEAT_POSI_3_MEM_SUCCED(3)
        EN_SEAT_POSI_MEM_SUCCED(4)
        EN_SEAT_POSI_MEM_FAIL(5)
        EN_PRESS_POSI(6)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            defaultValue = enSeatMemStsAndMsg.EN_INACTIVE;
        end

        function dScope = getDataScope()
            dScope = 'Auto';
        end

        function desc = getDescription()
            desc = '¼ÇÒä´æ´¢×´Ì¬:&#10;0x0: Inactive&#10;0x1: Seat position 1 memory succed&#10;0x2: Seat position 2 memory succed&#10;0x3: Seat position 3 memory succed&#10;0x4: Seat position memory succed&#10;0x5: Seat position memory fail&#10;0x6: Please press position 1,2,or 3 to conduct the memory of seat position¡££¨transmit when received ¡°SET¡± switch£©&#10;0x7: reserved,';
        end

        function headerFile = getHeaderFile()
            headerFile = '';
        end

        function flag = addClassNameToEnumNames()
            flag = true;
        end

    end
  
end
